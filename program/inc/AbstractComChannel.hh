#ifndef ABSTRACTCOMCHANNEL_HH
#define ABSTRACTCOMCHANNEL_HH

#include <mutex>

/*!
 * \brief Interfejs kanału komunikacyjnego.
 * * Definiuje metody, które musi implementować każdy kanał komunikacyjny
 * (np. oparty na gniazdach TCP).
 */
class AbstractComChannel {
public:
    /*!
     * \brief Wirtualny destruktor.
     * Konieczny dla poprawnego usuwania obiektów pochodnych przez wskaźnik bazowy.
     * Musi mieć implementację (nawet pustą), aby vtable została poprawnie wygenerowana.
     */
    virtual ~AbstractComChannel() {}

    /*!
     * \brief Inicjalizuje deskryptor gniazda.
     */
    virtual void Init(int Socket) = 0;

    /*!
     * \brief Udostępnia deskryptor pliku skojarzonego z połączeniem.
     */
    virtual int GetSocket() const = 0;

    /*!
     * \brief Zamyka dostęp do gniazda (blokuje mutex).
     */
    virtual void LockAccess() = 0;

    /*!
     * \brief Otwiera dostęp do gniazda (odblokowuje mutex).
     */
    virtual void UnlockAccess() = 0;

    /*!
     * \brief Udostępnia mutex chroniący dostęp do gniazda.
     * Metoda czysto wirtualna (= 0), ponieważ klasa abstrakcyjna
     * nie musi posiadać własnego obiektu mutexa (to rola klasy pochodnej).
     */
    virtual std::mutex &UseGuard() = 0;

    /*!
     * \brief Wysyła komunikat przez kanał.
     * \param[in] sMesg - wskaźnik na komunikat do wysłania (ciąg znaków zakończony '\0').
     * \retval liczba znaków wysłanych w ramach komunikatu,
     * \retval -1 w przypadku błędu.
     */
    virtual int Send(const char *sMesg) = 0;
};

#endif