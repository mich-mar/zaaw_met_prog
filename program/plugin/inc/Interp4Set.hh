#ifndef  COMMAND4SET_HH
#define  COMMAND4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include <iostream>
#include <string>
#include "AbstractInterp4Command.hh"
#include "Vector3D.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Set,
 * która modeluje polecenie ustawienia pozycji i orientacji obiektu.
 */

/*!
 * \brief Modeluje polecenie ustawienia pozycji i orientacji obiektu
 *
 * Klasa modeluje polecenie 'Set', które przyjmuje 6 parametrów:
 * Pozycja (X, Y, Z) oraz Orientacja (Roll, Pitch, Yaw).
 */
class Interp4Set: public AbstractInterp4Command {

  /**
   * @brief Przechowuje wczytane parametry polecenia
   */
  Vector3D _Pos_m;          // pozycja [m]
  double   _Roll_deg;       // [deg]
  double   _Pitch_deg;      // [deg]
  double   _Yaw_deg;        // [deg]

 public:
  /*!
   * \brief Domyślny konstruktor
   */
  Interp4Set();
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const override;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const override;
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() const override;

  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const override;

  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   *
   * Wykonuje polecenie oraz wizualizuje jego realizację.
   * \param[in,out]  rScn - scena zawierającą obiekty mobilne,
   * \param[in]      sMobObjName - wskaźnik na nazwę lokalizującą i identyfikującą obiekt,
   * \param[in,out]  rComChann - kanał komunikacyjny z serwerem graficznym.
   * \retval true - operacja powiodła się,
   * \retval false - w przypadku przeciwnym.
   */
  virtual bool ExecCmd( AbstractScene      &rScn, 
                        const char         *sMobObjName,
                        AbstractComChannel &rComChann ) override;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList) override;

  
  /*!
   * \brief Metoda fabryczna tworząca obiekt polecenia.
   */
  static AbstractInterp4Command* CreateCmd();
 };

#endif