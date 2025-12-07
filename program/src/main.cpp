/*!
 * @brief Główny plik wykonywalny interpretera poleceń (wersja uproszczona).
 *
 * Program wykonuje pięć głównych kroków:
 * 1. Wczytanie konfiguracji z pliku XML.
 * 2. Połączenie z serwerem i zainicjalizowanie sceny.
 * 3. Załadowanie wtyczek (komend) jako bibliotek .so.
 * 4. Wykonanie skryptu poleceń przetworzonego przez preprocesor.
 * 5. Sprzątanie i zakończenie działania.
 */

#include <iostream>
#include <dlfcn.h>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

#include "AbstractInterp4Command.hh"
#include "AbstractMobileObj.hh"
#include "Cuboid.hh"     
#include "preprocesor.hh"
#include "Configuration.hh"
#include "xmlinterp.hh"
#include "ComChannel.hh"

using Fun_CreateCmd = AbstractInterp4Command* (*)(void);
using Fun_GetCmdName = const char* (*)(void);

/**
 * @brief Konwertuje wektor 3D na format (x,y,z) zgodny z serwerem.
 */
std::string Vec2Str(const Vector3D& vec) {
    std::stringstream ss;
    ss << "(" << vec[0] << "," << vec[1] << "," << vec[2] << ")";
    return ss.str();
}

static void ExecSingleCommandLine(
    const std::string &cmdName,
    std::istream      &lineStream,
    const std::map<std::string, Fun_CreateCmd> &pluginCommands,
    AbstractScene     &scene,
    AbstractComChannel &channel
)
{
    auto it = pluginCommands.find(cmdName);
    if (it == pluginCommands.end()) {
        std::cerr << "!!! Nieznane polecenie: " << cmdName << std::endl;
        return;
    }

    AbstractInterp4Command *cmd = it->second();
    if (cmd == nullptr) {
        std::cerr << "!!! Blad CreateCmd() dla komendy: " << cmdName << std::endl;
        return;
    }

    std::string objName;
    const char *objCStr = nullptr;

    // Pause nie ma nazwy obiektu, reszta – ma
    if (cmdName != "Pause") {
        if (!(lineStream >> objName)) {
            std::cerr << "!!! Brak nazwy obiektu dla komendy: " << cmdName << std::endl;
            delete cmd;
            return;
        }
        objCStr = objName.c_str();
    }

    if (!cmd->ReadParams(lineStream)) {
        std::cerr << "!!! Blad parametrow polecenia: " << cmdName << std::endl;
        delete cmd;
        return;
    }

    std::cout << " Wykonuje: ";
    cmd->PrintCmd();

    if (!cmd->ExecCmd(scene, objCStr, channel)) {
        std::cerr << "!!! ExecCmd nie powiodlo sie dla komendy: "
                  << cmdName << std::endl;
    }

    delete cmd;
}

int main(int argc, char** argv)
{
    // ===============================================================
    // 0. Wczytywanie argumentów wywołania
    // ===============================================================
    if (argc != 3) {
        std::cerr << "Uzycie: " << argv[0]
                  << " plik_skrpyptu.cmd plik_konfiguracji.xml\n";
        return 1;
    }

    const char* scriptName = argv[1];
    const char* configName = argv[2];


    // ================================================================
    // 1. Wczytanie konfiguracji XML
    // ================================================================
    Configuration config;

    std::cout << "--- WCZYTYWANIE KONFIGURACJI ---\n";
    if (!ReadXML(configName, config)) return 1;

    // ================================================================
    // 2. Połączenie z serwerem i przygotowanie sceny
    // ================================================================
    std::cout << "--- POLACZENIE Z SERWEREM ---\n";
    ComChannel channel;

    if (!channel.InitConnection(6217)) {
        std::cerr << "!!! Blad polaczenia z serwerem\n";
        return 1;
    }

    // Czyścimy scenę po stronie serwera
    channel.Send("Clear\n");

    // Wysyłamy wszystkie obiekty z konfiguracji do serwera
    Scene& scene = config.GetScene();
    for (auto& [name, objPtr] : scene.GetObjects()) {

        // Każdy obiekt w XML to Cuboid – upewniamy się, że tak jest
        if (auto* cub = dynamic_cast<Cuboid*>(objPtr.get())) {

            // Tworzymy komendę AddObj zgodną z formatem serwera
            std::stringstream cmd;
            cmd << "AddObj Name=" << cub->GetName()
                << " RGB="      << Vec2Str(cub->GetColor())
                << " Scale="    << Vec2Str(cub->GetScale())
                << " Shift="    << Vec2Str(cub->GetShift())
                << " Trans_m="  << Vec2Str(cub->GetPositoin_m())
                << " RotXYZ_deg=("
                << cub->GetAng_Roll_deg()  << ","
                << cub->GetAng_Pitch_deg() << ","
                << cub->GetAng_Yaw_deg()   << ")\n";

            std::cout << " Wysylanie: " << cmd.str();
            channel.Send(cmd.str().c_str());

        } else {
            std::cerr << "!!! Obiekt '" << objPtr->GetName()
                      << "' nie jest typu Cuboid!\n";
        }
    }

    // ================================================================
    // 3. Ładowanie wtyczek (bibliotek .so)
    // ================================================================
    std::cout << "\n--- LADOWANIE WTYCZEK ---\n";

    std::map<std::string, Fun_CreateCmd> pluginCommands; // komendy: nazwa -> CreateCmd()
    std::vector<void*> pluginHandles;                    // uchwyty dlopen()

    std::vector<std::string> libraries;
    config.GetLibraries(libraries);

    for (const std::string& lib : libraries) {

        // Próba załadowania biblioteki
        void* handle = dlopen(lib.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "!!! Blad dlopen: " << dlerror() << "\n";
            continue;
        }

        // Pobieramy funkcje z biblioteki
        Fun_GetCmdName getName = reinterpret_cast<Fun_GetCmdName>(dlsym(handle, "GetCmdName"));
        Fun_CreateCmd create  = reinterpret_cast<Fun_CreateCmd>(dlsym(handle, "CreateCmd"));

        if (!getName || !create) {
            std::cerr << "!!! Wtyczka nie posiada wymaganych funkcji (" << lib << ")\n";
            dlclose(handle);
            continue;
        }

        // Rejestrujemy komendę
        std::string cmdName = getName();
        pluginCommands[cmdName] = create;
        pluginHandles.push_back(handle);

        std::cout << "  Zaladowano: " << cmdName << "\n";
    }

        // ================================================================
    // 4. Przetwarzanie skryptu (po preprocesorze) + akcje równoległe
    // ================================================================
    std::cout << "\n--- PRZETWARZANIE SKRYPTU ---\n";

    std::string preprocOutput = runPreprocesor(scriptName);
    std::istringstream scriptStream(preprocOutput);

    std::string line;
    while (std::getline(scriptStream, line)) {

        // pomijamy puste linie
        if (line.empty()) {
            continue;
        }

        // pomijamy komentarze zaczynające się od //
        {
            std::string trimmed = line;
            // proste ucięcie białych znaków z lewej:
            while (!trimmed.empty() && std::isspace(static_cast<unsigned char>(trimmed.front()))) {
                trimmed.erase(trimmed.begin());
            }
            if (trimmed.rfind("//", 0) == 0) {
                continue;
            }
        }

        std::istringstream lineStream(line);
        std::string cmdName;
        if (!(lineStream >> cmdName)) {
            continue; // linia bez komendy
        }

        if (cmdName == "Begin_Parallel_Actions") {
            // ==== Zbieramy linie aż do End_Parallel_Actions ====
            std::vector<std::string> parallelLines;
            while (std::getline(scriptStream, line)) {
                std::istringstream inner(line);
                std::string first;
                if (!(inner >> first)) {
                    continue; // pusta linia
                }
                if (first == "End_Parallel_Actions") {
                    break;
                }
                parallelLines.push_back(line);
            }

            // ==== Uruchamiamy każdą linię w osobnym wątku ====
            std::vector<std::thread> threads;
            for (const std::string &pl : parallelLines) {
                threads.emplace_back(
                    [&pluginCommands, &scene, &channel, pl]() {
                        std::istringstream ls(pl);
                        std::string innerCmd;
                        if (!(ls >> innerCmd)) {
                            return;
                        }
                        ExecSingleCommandLine(innerCmd, ls, pluginCommands, scene, channel);
                    }
                );
            }

            // ==== Czekamy, aż wszystkie wątki skończą ====
            for (std::thread &t : threads) {
                if (t.joinable()) {
                    t.join();
                }
            }
        }
        else {
            // Pojedyncza komenda – normalne wykonanie
            ExecSingleCommandLine(cmdName, lineStream, pluginCommands, scene, channel);
        }
    }



    // ================================================================
    // 5. Sprzątanie
    // ================================================================
    std::cout << "\n--- KONCZENIE PRACY ---\n";

    channel.Send("Close\n");   // zamknięcie sesji z serwerem

    // Zwalniamy biblioteki dynamiczne
    for (void* h : pluginHandles) {
        dlclose(h);
    }

    return 0;
}