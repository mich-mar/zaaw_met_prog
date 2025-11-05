cmake_minimum_required(VERSION 3.10.0)

project(InterpreterProject VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(XercesC REQUIRED)

option(BUILD_IN_DEBUG_MODE "Compile with debug flags" ON)

if(BUILD_IN_DEBUG_MODE)
    message(STATUS "Configuring in DEBUG mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
else()
    message(STATUS "Configuring in RELEASE mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
endif()

add_subdirectory(plugin)

add_executable(interp src/main.cpp 
                src/preprocesor.cpp
                src/xmlinterp.cpp)

# Kopiuje plik .spr do katalogu 'build', aby był dostępny dla programu 'interp'
configure_file(test_preproc.spr test_preproc.spr COPYONLY)

# Kopiuje plik config.xml do katalogu 'build'
configure_file(config.xml config.xml COPYONLY)

# Dodajemy katalog "inc" do ścieżek include
target_include_directories(interp PUBLIC inc ${XercesC_INCLUDE_DIR})

# Linkujemy bibliotekę 'dl' (niezbędna do dynamicznego ładowania pluginów)
target_link_libraries(interp PRIVATE dl ${XercesC_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(interp PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wformat=2
        -Wunused -Wnull-dereference -Wconversion -Wno-unused-parameter
    )
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(interp PRIVATE /W4 /WX)
endif()

# --- ZMIANA: Poprawione ustawienie RPATH ---
# Ustawiamy RPATH tak, aby program 'interp' uruchamiany z katalogu 'build'
# automatycznie znalazł bibliotekę .so w podkatalogu 'build/plugin'.
set_target_properties(interp PROPERTIES
    BUILD_RPATH "${CMAKE_BINARY_DIR}/plugin"
)

# -----------------------------------------------------------------------------
# Integracja z Doxygen
# -----------------------------------------------------------------------------
find_package(Doxygen)

if(DOXYGEN_FOUND)
    # Tworzy cel 'doc', który uruchamia Doxygen na podstawie pliku konfiguracyjnego.
    # Dokumentacja zostanie wygenerowana w miejscu określonym w Doxyfile.
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/dox/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/dox
        COMMENT "Generating API documentation with Doxygen..."
        VERBATIM
    )
else()
    # Jeśli Doxygen nie jest zainstalowany, cel 'doc' wyświetli komunikat.
    add_custom_target(doc
        COMMAND ${CMAKE_COMMAND} -E echo "Doxygen not found. Cannot generate documentation."
    )
endif()

# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Ulepszone cele pomocnicze i czyszczące
# -----------------------------------------------------------------------------
add_custom_target(show_help
    COMMAND ${CMAKE_COMMAND} -E echo "Dostępne cele:"
    COMMAND ${CMAKE_COMMAND} -E echo "  make            - Kompiluje program i wtyczkę"
    COMMAND ${CMAKE_COMMAND} -E echo "  make doc        - Generuje dokumentację (wymaga Doxygen)"
    COMMAND ${CMAKE_COMMAND} -E echo "  make clean      - Usuwa skompilowane pliki z katalogu 'build'"
    COMMAND ${CMAKE_COMMAND} -E echo "  make clean_all  - Gruntowne czyszczenie (dokumentacja, libs, pliki ~)"
)

# Cel do gruntownego czyszczenia, odpowiednik starego 'cleanall'
add_custom_target(clean_all

    # Czyści katalog libs, jeśli coś w nim zostało
    COMMAND rm -f ${CMAKE_SOURCE_DIR}/libs/*

    # Czyści dokumentację wygenerowaną przez Doxygen
    COMMAND rm -rf ${CMAKE_SOURCE_DIR}/dox/doc
    COMMAND rm -f ${CMAKE_SOURCE_DIR}/dox/doxy.log

    # Usuwa pliki tymczasowe (kończące się na ~) z całego projektu
    COMMAND find ${CMAKE_SOURCE_DIR} -name "*~" -delete
    COMMENT "Performing a deep clean..."
    VERBATIM
)

# -----------------------------------------------------------------------------