#include "Interp4Pause.hh"
#include "ComChannel.hh" 
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
 * @brief Domyślny konstruktor
 */
Interp4Pause::Interp4Pause()
  : _Time_ms(0)
{
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
bool Interp4Pause::ReadParams(std::istream &rStrm_CmdsList)
{
  // Pause czas_pauzy_ms
  if (!(rStrm_CmdsList >> _Time_ms)) {
    return false;
  }
  return true;
}

/**
 * @brief Wyświetla pełną postać polecenia (z wczytanym parametrem)
 */
void Interp4Pause::PrintCmd() const
{
  std::cout << GetCmdName() << "  " << _Time_ms << std::endl;
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
void Interp4Pause::PrintSyntax() const
{
  std::cout << "   Pause  CzasPauzy_ms" << std::endl;
}

/**
 * @brief Wyświetla same parametry
 */
void Interp4Pause::PrintParams() const
{
  std::cout << "   CzasPauzy: " << _Time_ms << " [ms]" << std::endl;
}

/**
 * @brief Wykonuje polecenie (na razie puste)
 */
bool Interp4Pause::ExecCmd(AbstractScene      &,
                           const char         *,
                           AbstractComChannel &)
{
    std::cout << "[Pause] " << _Time_ms << " ms\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(_Time_ms));
    return true;
}