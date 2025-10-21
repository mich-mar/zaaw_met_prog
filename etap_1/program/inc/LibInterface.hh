#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <string>
#include <memory>
#include "AbstractInterp4Command.hh" 

/*!
 * \brief Klasa opakowująca interfejs do dynamicznie ładowanej biblioteki wtyczki
 *
 * Zbiera wszystkie zmienne i odwołania odnoszące się do danej biblioteki/wtyczki.
 */
struct LibInterface {

    // Typ funkcji tworzącej polecenie.
    using CreateCmdFunc = AbstractInterp4Command* (*)(void);

    // Uchwyt do załadowanej biblioteki.
    void* LibHandler = nullptr;

    // Nazwa polecenia implementowanego przez tę bibliotekę.
    std::string CmdName;                 

    // Wskaźnik na funkcję tworzącą komendę.
    CreateCmdFunc _pCreateCmd = nullptr; 

    // Destruktor
    ~LibInterface() = default;

    // Fabryczna metoda tworząca instancję LibInterface.
    LibInterface() = default;
};

#endif