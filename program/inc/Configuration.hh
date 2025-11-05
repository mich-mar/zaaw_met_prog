#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <string>
#include <list>  

/**
 * @brief Przechowuje konfigurację wczytaną z zewnętrznego źródła (np. pliku XML).
 */
class Configuration {
private:
    /**
     * @brief Lista przechowująca nazwy bibliotek (np. "libInterp4Command.so").
     */
    std::list<std::string> _libraries;

    // TODO: Przewidziane miejsce na mapę obiektów sceny do wczytania
    // W przyszłości: std::map<std::string, SceneObject> _objects;

public:
    /**
     * @brief Konstruktor domyślny.
     */
    Configuration() = default;

    /**
     * @brief Dodaje nazwę biblioteki do wewnętrznej listy konfiguracji.
     *
     * @param libName - Nazwa biblioteki (np. z pliku .so) do dodania.
     */
    void AddLibrary(const std::string& libName) {
        _libraries.push_back(libName);
    }

    /**
     * @brief Kopiuje listę bibliotek do obiektu docelowego.
     *
     * @param[out] rLibList - Referencja do listy, która zostanie wypełniona nazwami bibliotek.
     */
    void GetLibraries(std::list<std::string>& rLibList) const {
        rLibList = _libraries; // Kopiowanie zawartości listy
    }
};

#endif // CONFIGURATION_HH