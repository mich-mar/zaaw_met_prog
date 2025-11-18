#ifndef CUBOID_HH
#define CUBOID_HH

#include "AbstractMobileObj.hh"
#include "Vector3D.hh"
#include <string>
#include <iostream>

/*!
 * \brief Klasa modelująca konkretny obiekt geometryczny (prostopadłościan).
 *
 * Dziedziczy po AbstractMobileObj i przechowuje parametry położenia,
 * orientacji oraz cechy wizualne (kolor, skala) wczytywane z XML.
 */
class Cuboid : public AbstractMobileObj {
    
    // --- Pola podstawowe (wymagane przez interfejs) ---
    Vector3D    _Position_m;     // Pozycja w metrach (Trans_m)
    Vector3D    _Ang_RPY_deg;    // Kąty Roll-Pitch-Yaw w stopniach
    std::string _Name;           // Nazwa obiektu (np. "Podstawa")

    // --- Pola dodatkowe (wymagane w Etapie 2 - konfiguracja XML) ---
    Vector3D    _Scale;          // Skala (domyślnie 1,1,1)
    Vector3D    _Shift;          // Przesunięcie lokalne (Shift)
    Vector3D    _ColorRGB;       // Kolor obiektu (R, G, B)

public:
    /*!
     * \brief Konstruktor domyślny inicjalizujący skalę na 1 i kolor na szary.
     */
    Cuboid() {
        // Ustawienie skali na (1, 1, 1)
        _Scale[0] = 1; _Scale[1] = 1; _Scale[2] = 1;

        // Ustawienie koloru na szary (128, 128, 128)
        _ColorRGB[0] = 128; _ColorRGB[1] = 128; _ColorRGB[2] = 128;

        // Wyzerowanie pozycji i orientacji
        for (int i = 0; i < 3; ++i) {
            _Shift[i] = 0;
            _Position_m[i] = 0;
            _Ang_RPY_deg[i] = 0;
        }
    }

    // ====================================================================
    // IMPLEMENTACJA METOD WIRTUALNYCH Z AbstractMobileObj
    // ====================================================================

    // --- Dostęp do kątów (Roll, Pitch, Yaw) [cite: 583, 593, 602] ---
    virtual double GetAng_Roll_deg() const override  { return _Ang_RPY_deg[0]; }
    virtual double GetAng_Pitch_deg() const override { return _Ang_RPY_deg[1]; }
    virtual double GetAng_Yaw_deg() const override   { return _Ang_RPY_deg[2]; }

    // --- Zmiana kątów [cite: 612, 621, 632] ---
    virtual void SetAng_Roll_deg(double Ang_Roll_deg) override   { _Ang_RPY_deg[0] = Ang_Roll_deg; }
    virtual void SetAng_Pitch_deg(double Ang_Pitch_deg) override { _Ang_RPY_deg[1] = Ang_Pitch_deg; }
    virtual void SetAng_Yaw_deg(double Ang_Yaw_deg) override     { _Ang_RPY_deg[2] = Ang_Yaw_deg; }

    // --- Dostęp do pozycji [cite: 641, 650] ---
    virtual const Vector3D & GetPositoin_m() const override { return _Position_m; }
    virtual void SetPosition_m(const Vector3D &rPos) override { _Position_m = rPos; }

    // --- Nazwa obiektu [cite: 659, 666] ---
    virtual void SetName(const char* sName) override { _Name = sName; }
    virtual const std::string & GetName() const override { return _Name; }


    // ====================================================================
    // METODY DODATKOWE (Dla parsera XML i komunikacji z serwerem)
    // ====================================================================

    // Ustawia skalę obiektu (z XML: Scale="...")
    void SetScale(const Vector3D &Scale) { _Scale = Scale; }
    const Vector3D & GetScale() const { return _Scale; }

    // Ustawia kolor obiektu (z XML: RGB="...")
    void SetColor(const Vector3D &Color) { _ColorRGB = Color; }
    const Vector3D & GetColor() const { return _ColorRGB; }

    // Ustawia przesunięcie lokalne (z XML: Shift="...")
    void SetShift(const Vector3D &Shift) { _Shift = Shift; }
    const Vector3D & GetShift() const { return _Shift; }
};

#endif