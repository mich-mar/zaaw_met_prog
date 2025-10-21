#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <string>
#include "AbstractInterp4Command.hh"

// Definicja typu wskaźnika na funkcję, która tworzy obiekt komendy.
using CreateCmdFunc = AbstractInterp4Command* (*)();

/*!
 * \brief Modeluje interfejs do biblioteki dynamicznej wtyczki.
 */
class LibInterface {
public:
    /*!
     * \brief Uchwyt do biblioteki dynamicznej.
     */
    void* pLibHnd = nullptr;

    /*!
     * \brief Nazwa polecenia, które jest udostępniane przez wtyczkę.
     */
    std::string CmdName;

    /*!
     * \brief Wskaźnik na funkcję tworzącą obiekt polecenia.
     */
    CreateCmdFunc pCreateCmd = nullptr;

    /*!
     * \brief Destruktor, który zwalnia bibliotekę.
     */
    ~LibInterface();
};

#endif // LIBINTERFACE_HH