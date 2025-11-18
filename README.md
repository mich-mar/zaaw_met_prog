# Instrukcja Kompilacji i Uruchomienia Projektu -- Etap 2

## **Wymagania wstępne**

-   System składa się z dwóch procesów (Serwer i Klient), które należy
    uruchamiać w osobnych terminalach.
-   Terminal wewnątrz VS Code (Snap) może powodować problemy z
    ładowaniem bibliotek Qt --- zastosuj specjalną komendę z `env -u`
    przy uruchamianiu serwera.

## **Krok 1: Instalacja zależności (jednorazowo)**

Serwer wymaga biblioteki SOIL:

    sudo apt-get update
    sudo apt-get install libsoil-dev

## **Krok 2: Kompilacja biblioteki QGLViewer**

    cd etap_2/serwer-z-tlem-Qt6/libQGLViewer/QGLViewer
    make clean
    rm libQGLViewer*.so*
    qmake
    make

Po kompilacji pojawią się pliki `.so`.

## **Krok 3: Kompilacja serwera graficznego**

    cd ../../serwer_zrodla
    make -f Makefile.server clean
    make -f Makefile.server QT=5

Powstanie plik wykonywalny serwera.

## **Krok 4: Uruchomienie serwera (Terminal 1)**

    cd etap_2/serwer-z-tlem-Qt6
    env -u QT_PLUGIN_PATH -u QML2_IMPORT_PATH LD_LIBRARY_PATH="$PWD/libQGLViewer/QGLViewer" ./serwer_graficzny

## **Krok 5: Uruchomienie klienta (Terminal 2)**

    cd program/build
    cmake ..
    make
    ./interp ../test_preproc.spr ../config.xml

## **TL;DR**

**Terminal 1:**

    cd /home/michal/Documents/studia/sem_7/zaaw_met_prog/etap_2/serwer-z-tlem-Qt6
    env -u QT_PLUGIN_PATH -u QML2_IMPORT_PATH LD_LIBRARY_PATH="$PWD/libQGLViewer/QGLViewer" ./serwer_graficzny

**Terminal 2:**

    cd program/build
    make && ./interp ../test_preproc.spr ../config.xml