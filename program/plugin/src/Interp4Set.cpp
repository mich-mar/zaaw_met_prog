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
 * @brief Domyślny konstruktor
 */
Interp4Set::Interp4Set()
{
  _Pos_m[0] = _Pos_m[1] = _Pos_m[2] = 0.0;
  _Roll_deg  = 0.0;
  _Pitch_deg = 0.0;
  _Yaw_deg   = 0.0;
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
bool Interp4Set::ReadParams(std::istream &rStrm_CmdsList)
{
  if (!(rStrm_CmdsList >> _Pos_m[0] >> _Pos_m[1] >> _Pos_m[2]
                       >> _Roll_deg >> _Pitch_deg >> _Yaw_deg)) {
    return false;
  }
  return true;
}

/**
 * @brief Wyświetla pełną postać polecenia (z wczytanymi parametrami)
 */
void Interp4Set::PrintCmd() const
{
  std::cout << GetCmdName() << "  "
       << _Pos_m[0] << " "
       << _Pos_m[1] << " "
       << _Pos_m[2] << "  "
       << _Roll_deg  << " "
       << _Pitch_deg << " "
       << _Yaw_deg   << std::endl;
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
void Interp4Set::PrintSyntax() const
{
  std::cout << "   Set  NazwaObiektu  x[m] y[m] z[m]  roll[deg] pitch[deg] yaw[deg]" << std::endl;
}

/**
 * @brief Wyświetla same parametry
 */
void Interp4Set::PrintParams() const
{
  std::cout << "   Pos: (" << _Pos_m[0] << ", " << _Pos_m[1] << ", " << _Pos_m[2] << ")"
       << "  Roll: "  << _Roll_deg
       << "  Pitch: " << _Pitch_deg
       << "  Yaw: "   << _Yaw_deg
       << std::endl;
}

/**
 * @brief Wykonuje polecenie (na razie puste)
 */
bool Interp4Set::ExecCmd(AbstractScene      &rScn,
                         const char         *sMobObjName,
                         AbstractComChannel &rComChann)
{
    if (sMobObjName == nullptr) {
        std::cerr << "Interp4Set::ExecCmd: brak nazwy obiektu\n";
        return false;
    }

    AbstractMobileObj *pObj = rScn.FindMobileObj(sMobObjName);
    if (pObj == nullptr) {
        std::cerr << "Interp4Set::ExecCmd: obiekt '"
                  << sMobObjName << "' nie znaleziony\n";
        return false;
    }

    // 1. aktualizacja sceny
    pObj->SetPosition_m(_Pos_m);
    pObj->SetAng_Roll_deg(_Roll_deg);
    pObj->SetAng_Pitch_deg(_Pitch_deg);
    pObj->SetAng_Yaw_deg(_Yaw_deg);

    // 2. przygotowanie komendy tekstowej
    std::ostringstream msg;
    msg << "UpdateObj Name=" << pObj->GetName()
        << " Trans_m=("
        << _Pos_m[0] << "," << _Pos_m[1] << "," << _Pos_m[2] << ")"
        << " RotXYZ_deg=("
        << _Roll_deg  << ","
        << _Pitch_deg << ","
        << _Yaw_deg   << ")\n";

    const std::string cmd = msg.str();

    // 3. wysłanie przez interfejs AbstractComChannel
    rComChann.LockAccess();

    if (rComChann.Send(cmd.c_str()) < 0) {
        std::cerr << "Interp4Set::ExecCmd: blad Send()\n";
        rComChann.UnlockAccess();
        return false;
    }

    rComChann.UnlockAccess();
    return true;
}

