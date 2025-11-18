#include "ComChannel.hh"
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

ComChannel::ComChannel() : _Socket(-1) {}

ComChannel::~ComChannel() {
    if (_Socket >= 0) {
        close(_Socket);
        std::cout << "--- Zamknieto gniazdo: " << _Socket << std::endl;
    }
}

// Zmiana nazwy metody na InitConnection
bool ComChannel::InitConnection(int Port) {
    struct sockaddr_in DaneAdSerw;

    // Czyszczenie struktury
    memset(&DaneAdSerw, 0, sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    DaneAdSerw.sin_port = htons(Port);

    _Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_Socket < 0) {
        std::cerr << "--- Blad otwarcia gniazda." << std::endl;
        return false;
    }

    if (connect(_Socket, (struct sockaddr*)&DaneAdSerw, sizeof(DaneAdSerw)) < 0) {
        std::cerr << "--- Brak mozliwosci polaczenia do portu: " << Port << std::endl;
        return false;
    }

    std::cout << " Nawiazano polaczenie z serwerem na porcie " << Port << std::endl;
    return true;
}


int ComChannel::Send(const char *sMesg) {
    if (_Socket < 0) {
        std::cerr << "--- Blad: Próba wysyłania przez nieaktywne gniazdo." << std::endl;
        return -1;
    }

    ssize_t IlWyslanych;
    ssize_t IlDoWyslania = (ssize_t) strlen(sMesg);

    while ((IlWyslanych = write(_Socket, sMesg, IlDoWyslania)) > 0) {
        IlDoWyslania -= IlWyslanych;
        sMesg += IlWyslanych;
    }

    if (IlWyslanych < 0) {
        std::cerr << "--- Blad przeslania napisu." << std::endl;
        return -1;
    }
    return 0;
}