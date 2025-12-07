#include "Interp4Rotate.hh"
#include "ComChannel.hh"
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
bool Interp4Rotate::ExecCmd(AbstractScene      &rScn,
                            const char         *sMobObjName,
                            AbstractComChannel &rComChann)
{
    if (sMobObjName == nullptr) {
        std::cerr << "Interp4Rotate::ExecCmd: brak nazwy obiektu\n";
        return false;
    }

    AbstractMobileObj *pObj = rScn.FindMobileObj(sMobObjName);
    if (pObj == nullptr) {
        std::cerr << "Interp4Rotate::ExecCmd: obiekt '"
                  << sMobObjName << "' nie znaleziony\n";
        return false;
    }

    if (_Angle_deg == 0.0 || _AngSpeed_deg_s == 0.0) {
        // nic do zrobienia
        return true;
    }

    double roll  = pObj->GetAng_Roll_deg();
    double pitch = pObj->GetAng_Pitch_deg();
    double yaw   = pObj->GetAng_Yaw_deg();

    const double ang_abs   = std::abs(_Angle_deg);
    const double speed_abs = std::abs(_AngSpeed_deg_s);
    double total_time = ang_abs / speed_abs;         // [s]

    const double dt_min = 0.01;                      // 20 ms
    int steps = static_cast<int>(total_time / dt_min);
    if (steps < 1) steps = 1;

    const double step_time  = total_time / steps;    // [s]
    const double step_angle = _Angle_deg / steps;    // [deg] (z uwzględnionym znakiem)

    for (int i = 0; i < steps; ++i) {
        if (_AxisName == "OX") {
            roll += step_angle;
        } else if (_AxisName == "OY") {
            pitch += step_angle;
        } else if (_AxisName == "OZ") {
            yaw += step_angle;
        } else {
            std::cerr << "Interp4Rotate::ExecCmd: nieznana os: '"
                      << _AxisName << "'\n";
            return false;
        }

        pObj->SetAng_Roll_deg(roll);
        pObj->SetAng_Pitch_deg(pitch);
        pObj->SetAng_Yaw_deg(yaw);

        std::ostringstream msg;
        msg << "UpdateObj Name=" << pObj->GetName()
            << " RotXYZ_deg=("
            << roll  << ","
            << pitch << ","
            << yaw   << ")\n";

        const std::string cmd = msg.str();

        rComChann.LockAccess();
        if (rComChann.Send(cmd.c_str()) < 0) {
            std::cerr << "Interp4Rotate::ExecCmd: blad Send()\n";
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
