#include "Interp4Set.hh"
#include <iostream>

/**
 * @brief Tworzy instancję obiektu polecenia (wersja C dla dlsym)
 */
extern "C" {
  AbstractInterp4Command* CreateCmd(void) {
    return Interp4Set::CreateCmd();
  }
}

/**
 * @brief Zwraca nazwę polecenia (wersja C dla dlsym)
 */
extern "C" {
  const char* GetCmdName(void) {
    return "Set";
  }
}

/**
 * @brief Statyczna metoda fabryczna
 */
AbstractInterp4Command* Interp4Set::CreateCmd() {
  return new Interp4Set();
}

/**
 * @brief Wczytuje 6 parametrów polecenia ze strumienia.
 */
bool Interp4Set::ReadParams(std::istream &rStrm_CmdsList) {
  if (!(rStrm_CmdsList >> _PosX_m >> _PosY_m >> _PosZ_m >> _Ang_Roll_deg >> _Ang_Pitch_deg >> _Ang_Yaw_deg)) {
    return false;
  }
  return true;
}

/**
 * @brief Wyświetla pełną postać polecenia (z wczytanymi parametrami)
 */
void Interp4Set::PrintCmd() const {
  std::cout << GetCmdName() << " " << _PosX_m << " " << _PosY_m << " " << _PosZ_m
            << " " << _Ang_Roll_deg << " " << _Ang_Pitch_deg << " " << _Ang_Yaw_deg << std::endl;
}

/**
 * @brief Zwraca nazwę polecenia
 */
const char* Interp4Set::GetCmdName() const {
  return "Set";
}

/**
 * @brief Wyświetla składnię polecenia
 */
void Interp4Set::PrintSyntax() const {
  std::cout << "Syntax: Set [X_m] [Y_m] [Z_m] [Roll_deg] [Pitch_deg] [Yaw_deg]" << std::endl;
}

/**
 * @brief Wyświetla same parametry
 */
void Interp4Set::PrintParams() const {
  std::cout << " Pos: (" << _PosX_m << ", " << _PosY_m << ", " << _PosZ_m << ")"
            << " Ang: (" << _Ang_Roll_deg << ", " << _Ang_Pitch_deg << ", " << _Ang_Yaw_deg << ")" << std::endl;
}

/**
 * @brief Wykonuje polecenie (na razie puste)
 */
bool Interp4Set::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) {
  std::cout << "ExecCmd for Set - not implemented in Stage 1." << std::endl;
  return true;
}