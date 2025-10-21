#ifndef PREPROCESOR_HPP
#define PREPROCESOR_HPP

#include <string>

/**
 * @brief Uruchamia preprocesor C (cpp) dla danego pliku i zwraca jego wyjście.
 * * Funkcja wykonuje polecenie systemowe "cpp [nazwaPliku]" i przechwytuje 
 * jego standardowe wyjście, zawierające kod z rozwiniętymi makrami 
 * i usuniętymi komentarzami.
 * * @param nazwaPliku Ścieżka do pliku (np. "prog.spr"), który ma zostać przetworzony.
 * @return std::string Zawartość pliku po przetworzeniu przez preprocesor.
 * @throws std::runtime_error Jeśli wykonanie polecenia popen nie powiodło się.
 */
std::string uruchomPreprocesor(const std::string& nazwaPliku);

#endif // PREPROCESOR_HPP