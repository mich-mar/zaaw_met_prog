#include "Interp4Pause.hh"
#include <iostream>

/**
 * @brief Tworzy instancję obiektu polecenia (wersja C dla dlsym)
 */
extern "C" {
  AbstractInterp4Command* CreateCmd(void) {
    return Interp4Pause::CreateCmd();
  }
}

/**
 * @brief Zwraca nazwę polecenia (wersja C dla dlsym)
 */
extern "C" {
  const char* GetCmdName(void) {
    return "Pause";
  }
}


/**
 * @brief Statyczna metoda fabryczna
 */
AbstractInterp4Command* Interp4Pause::CreateCmd() {
  return new Interp4Pause();
}

/**
 * @brief Wczytuje parametr polecenia (czas pauzy) ze strumienia.
 */
bool Interp4Pause::ReadParams(std::istream &rStrm_CmdsList) {
  // Wczytaj jeden parametr (unsigned int)
  if (!(rStrm_CmdsList >> _PauseTime_ms)) {
    return false;
  }
  return true;
}

/**
 * @brief Wyświetla pełną postać polecenia (z wczytanym parametrem)
 */
void Interp4Pause::PrintCmd() const {
  std::cout << GetCmdName() << " " << _PauseTime_ms << std::endl;
}

/**
 * @brief Zwraca nazwę polecenia
 */
const char* Interp4Pause::GetCmdName() const {
  return "Pause";
}

/**
 * @brief Wyświetla składnię polecenia
 */
void Interp4Pause::PrintSyntax() const {
  std::cout << "Syntax: Pause [PauseTime_ms]" << std::endl;
}

/**
 * @brief Wyświetla same parametry
 */
void Interp4Pause::PrintParams() const {
  std::cout << " PauseTime_ms: " << _PauseTime_ms << std::endl;
}

/**
 * @brief Wykonuje polecenie (na razie puste)
 */
bool Interp4Pause::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) {
  std::cout << "ExecCmd for Pause - not implemented in Stage 1." << std::endl;
  // W przyszłości: usleep(_PauseTime_ms * 1000); // usleep wymaga mikrosekund
  return true;
}