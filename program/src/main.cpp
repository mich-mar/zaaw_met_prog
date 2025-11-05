/**
 * @file
 * @brief Główny plik programu interpretera.
 *
 * Odpowiada za wczytanie konfiguracji XML, dynamiczne ładowanie wtyczek (pluginów),
 * uruchomienie preprocesora na pliku wsadowym oraz pętlę interpretera
 * wykonującą polecenia.
 */

#include <iostream>
#include <dlfcn.h>    
#include <cassert>
#include <string>
#include <sstream>
#include <cstdio>
#include <stdexcept>
#include <fstream>
#include <map>        
#include <list>         

#include "AbstractInterp4Command.hh"
#include "preprocesor.hh" 
#include "Configuration.hh"
#include "xmlinterp.hh"

/**
 * @brief Definicja typu wskaźnika na funkcję tworzącą polecenie.
 * Każda wtyczka musi udostępniać funkcję tego typu (np. "CreateCmd").
 */
using Fun_CreateCmd = AbstractInterp4Command* (*)(void);

/**
 * @brief Definicja typu wskaźnika na funkcję zwracającą nazwę polecenia.
 * Każda wtyczka musi udostępniać funkcję tego typu (np. "GetCmdName").
 */
using Fun_GetCmdName = const char* (*)(void);

/**
 * @brief Główna funkcja programu.
 */
int main()
{
  // ------------------------------------------------------------------==
  // 1. Wczytanie konfiguracji XML
  // ------------------------------------------------------------------==
  
  /**
   * @brief Obiekt przechowujący konfigurację wczytaną z XML.
   * Zawiera m.in. listę bibliotek (wtyczek) do załadowania.
   */
  Configuration config; 
  
  std::cout << "--- WCZYTYWANIE KONFIGURACJI (config.xml) ---" << std::endl;
  try {
    // Wywołujemy funkcję ReadXML z xmlinterp.hh
    if (!ReadXML("config.xml", config)) { 
      std::cerr << "!!! BŁĄD: Nie udało się wczytać 'config.xml'" << std::endl;
      return 1;
    }
  }
  catch (const std::runtime_error& e) {
    std::cerr << "!!! Błąd wykonania parsera XML: " << e.what() << std::endl;
    return 1;
  }

  // ------------------------------------------------------------------==
  // 2. Definicja struktur danych interpretera
  // ------------------------------------------------------------------==

  /**
   * @brief Mapa poleceń.
   * Kluczem jest nazwa polecenia (np. "Begin"), wartością jest wskaźnik
   * na funkcję tworzącą obiekt danej komendy (pobraną z wtyczki).
   */
  std::map<std::string, Fun_CreateCmd> commandMap;
  
  /**
   * @brief Lista uchwytów do załadowanych bibliotek dynamicznych.
   * Przechowywana, aby można było je poprawnie zamknąć na końcu programu.
   */
  std::list<void*> libraryHandles;

  // Pobierz listę bibliotek z obiektu Konfiguracji
  std::list<std::string> libraryNames;
  // Używamy funkcji GetLibraries z Configuration.hh
  config.GetLibraries(libraryNames); 

  std::cout << "--- ŁADOWANIE WTYCZEK (z config) ---" << std::endl;

  // ------------------------------------------------------------------==
  // 3. Pętla ładowania wtyczek
  // ------------------------------------------------------------------==
  
  /**
   * @brief Pętla iteruje po nazwach bibliotek pobranych z konfiguracji.
   */
  for (const std::string& libraryName : libraryNames) {
    void* pLibraryHandle = dlopen(libraryName.c_str(), RTLD_LAZY);

    if (!pLibraryHandle) {
      std::cerr << "!!! BŁĄD: Nie można otworzyć biblioteki: " << libraryName << std::endl;
      std::cerr << "!!!   " << dlerror() << std::endl;
      continue; 
    }

    // Pobranie funkcji GetCmdName
    void* pFun_GetCmdName = dlsym(pLibraryHandle, "GetCmdName");
    if (!pFun_GetCmdName) {
      std::cerr << "!!! BŁĄD: Nie znaleziono funkcji GetCmdName w " << libraryName << std::endl;
      dlclose(pLibraryHandle);
      continue;
    }
    Fun_GetCmdName GetName = reinterpret_cast<Fun_GetCmdName>(pFun_GetCmdName);

    // Pobranie funkcji CreateCmd
    void* pFun_CreateCmd = dlsym(pLibraryHandle, "CreateCmd");
    if (!pFun_CreateCmd) {
      std::cerr << "!!! BŁĄD: Nie znaleziono funkcji CreateCmd w " << libraryName << std::endl;
      dlclose(pLibraryHandle);
      continue;
    }
    Fun_CreateCmd CreateCommand = reinterpret_cast<Fun_CreateCmd>(pFun_CreateCmd);

    // Dodanie polecenia do mapy
    std::string commandName = GetName();
    commandMap[commandName] = CreateCommand;
    
    libraryHandles.push_back(pLibraryHandle); // Zapisanie uchwytu do zamknięcia
    std::cout << "  Załadowano polecenie: " << commandName << std::endl;
  }

  // ------------------------------------------------------------------==
  // 4. Uruchomienie preprocesora
  // ------------------------------------------------------------------==
  
  std::cout << "\n--- URUCHAMIANIE PREPROCESORA ---" << std::endl;
  
  const char* testFilename = "test_preproc.spr";
  
  /**
   * @brief Strumień (w pamięci) przechowujący kod po przetworzeniu 
   * przez preprocesor. Ten strumień będzie wejściem dla pętli 
   * interpretera.
   */
  std::stringstream commandStream; 
  
  std::ifstream testFile(testFilename);
  if (!testFile) {
      std::cerr << "!!! BŁĄD: Nie znaleziono pliku testowego '" << testFilename << "'" << std::endl;
  } else {
      testFile.close();
      try {
          std::string result = runPreprocesor(testFilename); 
          std::cout << "--- Zawartość " << testFilename << " po preprocesorze ---" << std::endl;
          std::cout << result;
          std::cout << "-----------------------------------------------" << std::endl;
          
          // Zapisanie wyniku preprocesora do strumienia poleceń
          commandStream.str(result);
      } catch (const std::runtime_error& e) {
          std::cerr << "!!! Błąd podczas testu preprocesora: " << e.what() << std::endl;
      }
  }

  // ------------------------------------------------------------------==
  // 5. Pętla interpretera poleceń
  // ------------------------------------------------------------------==
  
  std::cout << "\n--- URUCHAMIANIE INTERPRETERA ---" << std::endl;
  std::string commandName;

  /**
   * @brief Główna pętla interpretera.
   */
  while (commandStream >> commandName) {
    auto commandIter = commandMap.find(commandName);

    // Obsługa nieznanego polecenia
    if (commandIter == commandMap.end()) {
      std::cerr << "!!! BŁĄD: Nierozpoznane polecenie: " << commandName << std::endl;
      std::string restOfLine;
      std::getline(commandStream, restOfLine); // Pomiń resztę linii
      continue;
    }

    // Utworzenie obiektu polecenia
    Fun_CreateCmd pCreateCommand = commandIter->second;
    AbstractInterp4Command *pCommand = pCreateCommand();

    std::cout << "\n> Wykonywanie polecenia: " << pCommand->GetCmdName() << std::endl;

    // Wczytanie parametrów i wykonanie
    if (!pCommand->ReadParams(commandStream)) {
      std::cerr << "!!! BŁĄD: Niepoprawne parametry dla polecenia: " << commandName << std::endl;
      pCommand->PrintSyntax(); 
    } else {
      pCommand->PrintCmd();
    }
    
    delete pCommand; // Zwolnienie pamięci
  }

  // ------------------------------------------------------------------==
  // 6. Zamykanie bibliotek
  // ------------------------------------------------------------------==
  
  /**
   * @brief Sprzątanie - zwalnianie uchwytów do bibliotek dynamicznych.
   */
  std::cout << "\n--- ZAMYKANIE BIBLIOTEK ---" << std::endl;
  for (void* pLibraryHandle : libraryHandles) {
    dlclose(pLibraryHandle);
  }

  return 0;
}