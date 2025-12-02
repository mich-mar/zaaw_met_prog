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

int main()
{
    // ================================================================
    // 1. Wczytanie konfiguracji XML
    // ================================================================
    Configuration config;

    std::cout << "--- WCZYTYWANIE KONFIGURACJI ---\n";
    if (!ReadXML("config.xml", config)) {
        return 1;   // krytyczny błąd – przerwij program
    }

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
    // 4. Przetwarzanie skryptu (po preprocesorze)
    // ================================================================
    std::cout << "\n--- PRZETWARZANIE SKRYPTU ---\n";

    const char* script = "skrypt.spr";

    // Sprawdzamy czy plik istnieje
    if (!std::ifstream(script)) {
        std::cerr << "!!! Brak pliku: " << script << "\n";
    } 
    else 
    {
        // Uruchamiamy preprocesor (obsługuje m.in. #include)
        std::string preprocOutput = runPreprocesor(script);
        std::stringstream ss(preprocOutput);

        std::string cmdName;
        while (ss >> cmdName) {

            // Sprawdzamy czy komenda istnieje
            if (!pluginCommands.count(cmdName)) {
                std::cerr << "!!! Nieznane polecenie: " << cmdName << "\n";
                std::string dummy; 
                std::getline(ss, dummy); // pomijamy resztę linii
                continue;
            }

            // Tworzymy obiekt komendy
            AbstractInterp4Command* cmd = pluginCommands[cmdName]();

            // Wczytanie parametrów
            if (cmd->ReadParams(ss)) {
                std::cout << " Wykonuje: ";
                cmd->PrintCmd();
                // TU w kolejnych etapach wywołanie: cmd->ExecCmd(...)
            } 
            else {
                std::cerr << "!!! Blad parametrow polecenia\n";
            }

            delete cmd;
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