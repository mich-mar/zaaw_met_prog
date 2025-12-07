#include "Interp4Rotate.hh"
#include <iostream>

/**
 * @brief Tworzy instancję obiektu polecenia
 */
extern "C" {
  AbstractInterp4Command* CreateCmd(void) {
    return new Interp4Rotate();
  }
}

/**
 * @brief Zwraca nazwę polecenia
 */
extern "C" {
  const char* GetCmdName(void) {
    return "Rotate";
  }
}

/**
 * @brief Konstruktor domyślny
 */
Interp4Rotate::Interp4Rotate()
: _AxisName("OZ"), _AngSpeed_deg_s(0.0), _Angle_deg(0.0)
{}

/**
 * @brief Wczytuje parametry polecenia (3x double) ze strumienia.
 */
bool Interp4Rotate::ReadParams(std::istream &rStrm_CmdsList)
{
  if (!(rStrm_CmdsList >> _AxisName >> _AngSpeed_deg_s >> _Angle_deg)) {
    return false;
  }
  return true;
}

/**
 * @brief Wyświetla pełną postać polecenia (z wczytanymi parametrami)
 */
void Interp4Rotate::PrintCmd() const
{
  std::cout << GetCmdName() << "  "
       << _AxisName << "  "
       << _AngSpeed_deg_s << "  "
       << _Angle_deg << std::endl;
}

/**
 * @brief Zwraca nazwę polecenia
 */
const char* Interp4Rotate::GetCmdName() const {
  return "Rotate";
}

/**
 * @brief Wyświetla składnię polecenia
 */
void Interp4Rotate::PrintSyntax() const
{
  std::cout << "   Rotate  NazwaObiektu  OX|OY|OZ  SzybkoscKatowa[deg/s]  KatObrotu[deg]" << std::endl;
}
/**
 * @brief Wyświetla same parametry
 */
void Interp4Rotate::PrintParams() const
{
  std::cout << "   Oś: " << _AxisName
       << "  SzybkoscKatowa: " << _AngSpeed_deg_s << " [deg/s]"
       << "  KatObrotu: " << _Angle_deg << " [deg]"
       << std::endl;
}

/**
 * @brief Wykonuje polecenie (na razie puste)
 */
bool Interp4Rotate::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) {
  std::cout << "ExecCmd for Rotate - not implemented in Stage 1." << std::endl;
  return true;
}