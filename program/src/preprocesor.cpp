#include "preprocesor.hh"
#include <iostream>
#include <sstream>
#include <cstdio>
#include <stdexcept>

#define BUFFER_SIZE 512

std::string runPreprocesor(const std::string& nazwaPliku) {
    
    std::string polecenie = "cpp -P " + nazwaPliku;
    FILE* potok = popen(polecenie.c_str(), "r");
    
    if (!potok) {
        throw std::runtime_error("BŁĄD: Wywołanie popen() nie powiodło się!");
    }

    char bufor[BUFFER_SIZE];
    std::ostringstream strumienWynikowy;

    while (fgets(bufor, BUFFER_SIZE, potok) != nullptr) {
        strumienWynikowy << bufor;
    }

    pclose(potok);
    return strumienWynikowy.str();
}