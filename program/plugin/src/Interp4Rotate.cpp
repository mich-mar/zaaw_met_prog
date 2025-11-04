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
 * @brief Wczytuje parametry polecenia (3x double) ze strumienia.
 */
bool Interp4Rotate::ReadParams(std::istream &rStrm_CmdsList) {
  if (!(rStrm_CmdsList >> _AngVel_Roll_deg_s >> _AngVel_Pitch_deg_s >> _AngVel_Yaw_deg_s)) {
    // Jeśli się nie udało (np. koniec pliku, zły format)
    return false;
  }
  return true;
}

/**
 * @brief Wyświetla pełną postać polecenia (z wczytanymi parametrami)
 */
void Interp4Rotate::PrintCmd() const {
  std::cout << GetCmdName() << " " << _AngVel_Roll_deg_s << " " << _AngVel_Pitch_deg_s << " " << _AngVel_Yaw_deg_s << std::endl;
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
void Interp4Rotate::PrintSyntax() const {
  std::cout << "Syntax: Rotate [AngVel_Roll] [AngVel_Pitch] [AngVel_Yaw]" << std::endl;
}

/**
 * @brief Wyświetla same parametry
 */
void Interp4Rotate::PrintParams() const {
  std::cout << " Roll: " << _AngVel_Roll_deg_s << ", Pitch: " << _AngVel_Pitch_deg_s << ", Yaw: " << _AngVel_Yaw_deg_s << std::endl;
}

/**
 * @brief Wykonuje polecenie (na razie puste)
 */
bool Interp4Rotate::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) {
  std::cout << "ExecCmd for Rotate - not implemented in Stage 1." << std::endl;
  return true;
}