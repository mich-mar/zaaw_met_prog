#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <string>
#include <vector>
#include "Scene.hh"

/**
 * @brief Przechowuje konfigurację wczytaną z zewnętrznego źródła (np. pliku XML).
 */
class Configuration {
private:
    /**
     * @brief Wektor przechowujący nazwy bibliotek.
     */
    std::vector<std::string> _libraries;

    /**
     * @brief Obiekt sceny przechowujący obiekty mobilne.
     */
    Scene _Scene;              

public:
    Configuration() = default;

    void AddLibrary(const std::string& libName) {
        _libraries.push_back(libName);
    }

    Scene& GetScene() { return _Scene; }

    /**
     * @brief Kopiuje wektor bibliotek do wektora wyjściowego.
     */
    void GetLibraries(std::vector<std::string>& rLibList) const {
        rLibList = _libraries;
    }
};

#endif // CONFIGURATION_HH
