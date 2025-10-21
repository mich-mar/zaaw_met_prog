#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
// #include "preprocesor.hpp" 
#include <string>
#include <sstream>
#include <cstdio>
#include <stdexcept>
#include <fstream> 


int main()
{
  // Wskaźniki na funkcję tworzącą obiekt komendy (CreateCmd)
  AbstractInterp4Command *(*pCreateCmd_Rotate)(void);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  void *pFun;
  
  // ====================================================================
  // 1. Ładowanie i testowanie pluginu Interp4Rotate
  // ====================================================================

  void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
  
  if (!pLibHnd_Rotate) {
    std::cerr << "!!! Brak biblioteki: libInterp4Rotate.so" << std::endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFun) {
    std::cerr << "!!! Interp4Rotate: Nie znaleziono funkcji CreateCmd" << std::endl;
    dlclose(pLibHnd_Rotate); return 1;
  }
  pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
  AbstractInterp4Command *pCmd_Rotate = pCreateCmd_Rotate();

  std::cout << "\n--- TESTOWANIE KOMENDY: " << pCmd_Rotate->GetCmdName() << " ---" << std::endl;
  pCmd_Rotate->PrintSyntax();
  pCmd_Rotate->PrintCmd();
  
  delete pCmd_Rotate;

  // ====================================================================
  // 2. Ładowanie i testowanie pluginu Interp4Move
  // ====================================================================

  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);

  if (!pLibHnd_Move) {
    std::cerr << "!!! Brak biblioteki: libInterp4Move.so" << std::endl;
    dlclose(pLibHnd_Rotate); return 1;
  }

  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    std::cerr << "!!! Interp4Move: Nie znaleziono funkcji CreateCmd" << std::endl;
    dlclose(pLibHnd_Rotate); dlclose(pLibHnd_Move); return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
  AbstractInterp4Command *pCmd_Move = pCreateCmd_Move();

  std::cout << "\n--- TESTOWANIE KOMENDY: " << pCmd_Move->GetCmdName() << " ---" << std::endl;
  pCmd_Move->PrintSyntax();
  pCmd_Move->PrintCmd();

  delete pCmd_Move;

  // ====================================================================
  // 3. Testowanie Preprocesora
  // ====================================================================
  
  // std::cout << "\n--- TESTOWANIE PREPROCESORA ---" << std::endl;
  
  // const char* nazwaPlikuTestowego = "test_preproc.spr";
  
  // // 3.1. Sprawdź, czy plik testowy istnieje
  // std::ifstream plikTestowy(nazwaPlikuTestowego);
  // if (!plikTestowy) {
  //     std::cerr << "!!! BŁĄD: Brak pliku testowego '" << nazwaPlikuTestowego << "'" << std::endl;
  //     std::cerr << "!!! Utwórz go ręcznie przed uruchomieniem testu." << std::endl;
  // } else {
  //     plikTestowy.close(); // Plik istnieje, możemy go zamknąć i kontynuować
  //     std::cout << "Znaleziono plik testowy: " << nazwaPlikuTestowego << std::endl;

  //     // 3.2. Uruchom preprocesor na tym pliku
  //     try {
  //         std::string wynik = uruchomPreprocesor(nazwaPlikuTestowego);
  //         std::cout << "--- Wynik z preprocesora ---" << std::endl;
  //         std::cout << wynik;
  //         std::cout << "----------------------------" << std::endl;

  //         // 3.3. Sprawdź poprawność (asercje)
          
  //         // Sprawdź, czy makra się rozwinęły
  //         assert(wynik.find("linia_z_makrem 123 456") != std::string::npos);
  //         assert(wynik.find("inna_linia 40 40") != std::string::npos);
          
  //         // Sprawdź, czy komentarze zniknęły
  //         assert(wynik.find("Komentarz do usunięcia") == std::string::npos);
  //         assert(wynik.find("komentarz blokowy") == std::string::npos);
          
  //         std::cout << "Testy preprocesora ZALICZONE." << std::endl;

  //     } catch (const std::runtime_error& e) {
  //         std::cerr << "!!! Błąd podczas testu preprocesora: " << e.what() << std::endl;
  //     }
  // }

  // ====================================================================
  // 4. Zamykanie bibliotek
  // ====================================================================
  
  dlclose(pLibHnd_Rotate);
  dlclose(pLibHnd_Move);

  return 0;
}