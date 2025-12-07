#include "Interp4Move.hh"
#include <iostream>

/**
 * @brief Tworzy instancję obiektu polecenia
 */
extern "C" {
  AbstractInterp4Command* CreateCmd(void) {
    return new Interp4Move();
  }
}

/**
 * @brief Zwraca nazwę polecenia
 */
extern "C" {
  const char* GetCmdName(void) {
    return "Move";
  }
}

/**
 * @brief Wczytuje parametry polecenia (3x double) ze strumienia.
 * * To jest kluczowa funkcja, która rozwiązuje Twój błąd.
 * Czyta 3 liczby ze strumienia, "zabierając" je z niego,
 * aby główna pętla interpretera mogła wczytać następne polecenie.
 */
bool Interp4Move::ReadParams(std::istream &rStrm_CmdsList)
{
  if (!(rStrm_CmdsList >> _Speed >> _Distance)) {
    return false;
  }
  return true;
}

/**
 * @brief Wyświetla pełną postać polecenia (z wczytanymi parametrami)
 */
void Interp4Move::PrintCmd() const
{
  std::cout << GetCmdName() << "  "
       << _Speed << "  " << _Distance << std::endl;
}
/**
 * @brief Zwraca nazwę polecenia
 */
const char* Interp4Move::GetCmdName() const {
  return "Move";
}

/**
 * @brief Wyświetla składnię polecenia
 */
void Interp4Move::PrintSyntax() const
{
  std::cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << std::endl;
}

/**
 * @brief Wyświetla same parametry
 */
void Interp4Move::PrintParams() const
{
  std::cout << "   Szybkosc: " << _Speed
       << "  DlugoscDrogi: " << _Distance << std::endl;
}


/**
 * @brief Wykonuje polecenie (na razie puste)
 */
bool Interp4Move::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) {
  std::cout << "ExecCmd for Move - not implemented in Stage 1." << std::endl;
  return true;
}