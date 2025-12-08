# Instrukcja instalacji — interp4cmds

`interp4cmds` wykorzystuje standardowy system budowania **GNU Autotools**.
Ten dokument opisuje proces konfiguracji, kompilacji i instalacji pakietu.

---

## 1. Przygotowanie konfiguracji

Aby wygenerować pliki autotools i przygotować projekt, wykonaj:

```
libtoolize
autoreconf --install
./configure
```

Domyślny katalog instalacji to:

```
/usr/local/
```

---

## 1.1. Wybór własnego katalogu instalacji

```
./configure --prefix=$HOME/interp4cmds
```

---

## 1.2. Wskazanie niestandardowej lokalizacji Xerces-C (opcjonalne)

```
./configure \
  CXXFLAGS="-I/ścieżka/do/include" \
  LDFLAGS="-L/ścieżka/do/lib"
```

---

## 2. Kompilacja programu i wtyczek

Aby zbudować interpreter i wszystkie moduły:

```
make
```

Po udanej kompilacji powstają:

- plik wykonywalny: **interp4cmds**  
- biblioteki-wtyczki:  
  - `libInterp4Move.so`
  - `libInterp4Rotate.so`
  - `libInterp4Pause.so`
  - `libInterp4Set.so`

---

## 3. Instalacja

Zainstalowanie programu i wtyczek:

```
make install
```

Instalowane są:

- `bin/interp4cmds`
- `lib/libInterp4*.so`

---

## 4. Deinstalacja

```
make uninstall
```

---

## 5. Test pakietu (dystrybucja + walidacja)

Autotools udostępnia polecenie:

```
make distcheck
```

Test ten:

1. tworzy archiwum `.tar.gz`,  
2. rozpakowuje je w katalogu tymczasowym,  
3. wykonuje `./configure`, `make`, `make install`, `make uninstall`,  
4. sprawdza poprawność budowy i instalacji.

Po ukończeniu otrzymasz gotowy pakiet:

```
interp4cmds-<wersja>.tar.gz
```

---

## 6. Struktura katalogów po instalacji

```
PREFIX/
 ├── bin/
 │   └── interp4cmds
 ├── lib/
 │   ├── libInterp4Move.so
 │   ├── libInterp4Rotate.so
 │   ├── libInterp4Pause.so
 │   └── libInterp4Set.so
 └── share/doc/interp4cmds/   (opcjonalnie)
```

---

## 7. Zależności

- **Xerces-C** — parser XML  
- **POSIX sockets** — komunikacja TCP  
- **libtool** — budowanie bibliotek `.so`  
- **C++17** lub nowszy standard  

Instalacja biblioteki Xerces-C na Ubuntu/Debian:

```
sudo apt install libxerces-c-dev
```

---

## 8. Rozwiązywanie problemów

### Błąd: „Brak naglowkow biblioteki xerces-c”

Zainstaluj pakiet:

```
sudo apt install libxerces-c-dev
```

lub wskaż ścieżki:

```
./configure CXXFLAGS="-I/usr/include" LDFLAGS="-L/usr/lib"
```

---

### Błąd: „make distcheck” wymaga README / INSTALL

Upewnij się, że `Makefile.am` zawiera:

```
dist_doc_DATA = README.md INSTALL.md LICENSE
```

---

## 9. Uruchamianie programu

```
interp4cmds skrypt.spr config.xml
```

Interpreter:

- wczytuje scenę,  
- ładuje wtyczki,  
- interpretuje skrypt,  
- przesyła komendy do serwera graficznego.

---

Koniec pliku INSTALL.md
