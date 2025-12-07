#include "Interp4Move.hh"
#include "ComChannel.hh" 
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
bool Interp4Move::ExecCmd(AbstractScene      &rScn,
                          const char         *sMobObjName,
                          AbstractComChannel &rComChann)
{
    if (sMobObjName == nullptr) {
        std::cerr << "Interp4Move::ExecCmd: brak nazwy obiektu\n";
        return false;
    }

    AbstractMobileObj *pObj = rScn.FindMobileObj(sMobObjName);
    if (pObj == nullptr) {
        std::cerr << "Interp4Move::ExecCmd: obiekt '"
                  << sMobObjName << "' nie znaleziony\n";
        return false;
    }

    if (_Distance == 0.0 || _Speed == 0.0) {
        // nic do zrobienia – ale nie traktujemy jako błąd
        return true;
    }

    Vector3D pos = pObj->GetPositoin_m();

    const double dist_abs  = std::abs(_Distance);
    const double speed_abs = std::abs(_Speed);
    double total_time = dist_abs / speed_abs;        // [s]

    // Parametry dyskretyzacji animacji
    const double dt_min = 0.01;                      // minimalny krok czasu [s] (20 ms)
    int steps = static_cast<int>(total_time / dt_min);
    if (steps < 1) steps = 1;

    const double step_time   = total_time / steps;   // [s]
    const double step_dist   = _Distance / steps;    // [m] (z uwzględnionym znakiem)

    // Kierunek ruchu – zgodnie z yaw
    const double yaw_deg = pObj->GetAng_Yaw_deg();
    const double yaw_rad = yaw_deg * M_PI / 180.0;
    const double dir_x   = std::cos(yaw_rad);
    const double dir_y   = std::sin(yaw_rad);

    for (int i = 0; i < steps; ++i) {
        pos[0] += dir_x * step_dist;
        pos[1] += dir_y * step_dist;
        // pos[2] zostaje bez zmian

        pObj->SetPosition_m(pos);

        std::ostringstream msg;
        msg << "UpdateObj Name=" << pObj->GetName()
            << " Trans_m=("
            << pos[0] << "," << pos[1] << "," << pos[2] << ")\n";

        const std::string cmd = msg.str();

        rComChann.LockAccess();
        if (rComChann.Send(cmd.c_str()) < 0) {
            std::cerr << "Interp4Move::ExecCmd: blad Send()\n";
            rComChann.UnlockAccess();
            return false;
        }
        rComChann.UnlockAccess();

        std::this_thread::sleep_for(
            std::chrono::duration<double>(step_time)
        );
    }

    return true;
}
