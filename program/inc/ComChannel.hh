#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

#include "AbstractComChannel.hh"
#include <mutex>
#include <string>

/*!
 * \brief Klasa realizująca połączenie sieciowe z serwerem.
 * * Implementuje interfejs AbstractComChannel.
 * Bazuje na mechanizmie gniazd (sockets) zaimplementowanym w przykładowym kliencie.
 */
class ComChannel : public AbstractComChannel {
    /*!
     * \brief Deskryptor gniazda sieciowego.
     */
    int _Socket = -1;

    /*!
     * \brief Mutex do synchronizacji dostępu (wymagany przez interfejs).
     */
    std::mutex _Mutex;

public:
    /*!
     * \brief Konstruktor i destruktor.
     */
    ComChannel();
    ~ComChannel();

    /*!
     * \brief Inicjalizuje połączenie z serwerem.
     * * \param Port - numer portu, na którym nasłuchuje serwer (domyślnie 6217).
     * \retval true - połączenie nawiązane.
     * \retval false - błąd połączenia.
     */
    bool InitConnection(int Port);

    /*!
     * \brief Wysyła napis do serwera.
     * * Implementacja bazuje na funkcji Send z przykładowego klienta.
     * \param sMsg - napis do wysłania (musi kończyć się znakiem nowej linii).
     * \return Ilość wysłanych bajtów lub wartość ujemna w przypadku błędu.
     */
    int Send(const char *sMsg);

    // --- Metody wirtualne z AbstractComChannel ---
    
    /*! \brief Inicjalizacja deskryptora (z interfejsu) */
    virtual void Init(int Socket) override { _Socket = Socket; }
    
    /*! \brief Pobranie deskryptora */
    virtual int GetSocket() const override { return _Socket; }
    
    /*! \brief Zablokowanie dostępu (mutex) */
    virtual void LockAccess() override { _Mutex.lock(); }
    
    /*! \brief Odblokowanie dostępu (mutex) */
    virtual void UnlockAccess() override { _Mutex.unlock(); }
    
    /*! \brief Dostęp do strażnika mutexa */
    virtual std::mutex &UseGuard() override { return _Mutex; }
};

#endif