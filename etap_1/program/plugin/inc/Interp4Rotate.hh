#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego obrót
 */
class Interp4Rotate: public AbstractInterp4Command {

  double  _Angle_deg;  /*!< Kąt obrotu w stopniach */

public:

  /*!
   * \brief
   */
  Interp4Rotate();  

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
  virtual void PrintParams() const override {} 

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
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static AbstractInterp4Command* CreateCmd();

};

#endif
