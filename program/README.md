# interp4cmds — Interpreter Poleceń 3D z Dynamicznymi Wtyczkami

`interp4cmds` jest modularnym interpretem poleceń służącym do sterowania
obiektami 3D w scenie renderowanej przez zewnętrzny serwer graficzny.
Projekt realizuje wymagania zadania laboratoryjnego z kursu
**Zaawansowane Metody Programowania**.

Interpreter umożliwia:

* wczytywanie konfiguracji sceny z plików XML (biblioteka **Xerces-C**),
* dynamiczne ładowanie bibliotek-wtyczek (`.so`) definiujących polecenia,
* wykonywanie sekwencji komend z plików skryptowych `.spr`,
* obsługę sekcji równoległych (`Begin_Parallel_Actions`),
* komunikację TCP z serwerem graficznym,
* obsługę preprocesora (#include) w skryptach.

---

## Funkcjonalności

### Wbudowane typy poleceń (ładowane jako wtyczki)

* **Move** — przesunięcie obiektu wzdłuż lokalnej osi X,
* **Rotate** — obrót obiektu względem osi OX/OY/OZ,
* **Set** — natychmiastowe ustawienie pozycji i orientacji,
* **Pause** — zatrzymanie wykonywania na określony czas (ms).

Każda komenda jest osobną biblioteką `.so`, ładowaną podczas startu programu.

### Architektura systemu

* interfejsy abstrakcyjne:

  * `AbstractInterp4Command`
  * `AbstractMobileObj`
  * `AbstractScene`
  * `AbstractComChannel`
* dynamiczne wczytywanie modułów (`dlopen`, `dlsym`),
* przejrzysty system rozszerzeń — dodanie nowego polecenia wymaga stworzenia nowej biblioteki `.so`,
* komunikacja z serwerem graficznym poprzez gniazda TCP.

---

## Struktura projektu

```
program/
├── inc/           # nagłówki interfejsów i klas
├── src/           # implementacja interpretera
├── plugin/        # implementacje poleceń (.cpp + .hh)
├── config.xml     # konfiguracja sceny (przykład)
├── skrypt.spr     # skrypt poleceń (przykład)
├── README.md
└── INSTALL.md
```

---

## Wymagania

* kompilator **C++17** lub nowszy,
* biblioteka **Xerces-C**
  (np. `sudo apt install libxerces-c-dev`),
* narzędzia GNU Autotools:

  * `autoconf`
  * `automake`
  * `libtool`
* system Linux zgodny z POSIX.

---

## Skrócona instrukcja kompilacji i instalacji

Najprostszy sposób:

```
./configure
make
make install
```

Pełna instrukcja, w tym wskazanie niestandardowych katalogów i instalacja z repozytorium źródłowego, znajduje się w **INSTALL.md**.

---

## Przykład uruchomienia

```
interp4cmds skrypt.spr config.xml
```

Podczas pracy interpreter:

1. wczytuje konfigurację sceny z pliku XML,
2. ładuje wszystkie zdefiniowane wtyczki (`libInterp4*.so`),
3. interpretuje komendy ze skryptu `.spr`,
4. wysyła zmiany do serwera graficznego.

---

## Licencja

Projekt udostępniony na licencji **MIT**.
Pełny tekst licencji znajduje się w pliku `LICENSE`.

---

## Autor

**Michał Markuzel, 275417**

*Projekt zrealizowany w ramach kursu **Zaawansowane Metody Programowania**.*