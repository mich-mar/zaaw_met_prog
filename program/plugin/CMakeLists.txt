# Tworzymy bibliotekę współdzieloną (.so)/(.dylib) o nazwie "Interp4Move"
add_library(Interp4Move SHARED src/Interp4Move.cpp)

# Dodajemy katalog "inc" (wewnątrz pluginu) do ścieżek include
target_include_directories(Interp4Move PUBLIC inc)

# Dodajemy główny katalog "inc" projektu do ścieżek include
target_include_directories(Interp4Move PUBLIC ${CMAKE_SOURCE_DIR}/inc)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Interp4Move PRIVATE
        -fPIC
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wformat=2
        -Wunused
        -Wnull-dereference
        -Wconversion
        -Wno-unused-parameter
    )
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(Interp4Move PRIVATE /W4 /WX)
endif()

# -----------------------------------------------------------------------------
# --- DODANO DEFINICJĘ DLA Interp4Rotate ---
# -----------------------------------------------------------------------------

# Tworzymy bibliotekę współdzieloną (.so)/(.dylib) o nazwie "Interp4Rotate"
add_library(Interp4Rotate SHARED src/Interp4Rotate.cpp)

# Dodajemy katalog "inc" (wewnątrz pluginu) do ścieżek include
target_include_directories(Interp4Rotate PUBLIC inc)

# Dodajemy główny katalog "inc" projektu do ścieżek include
target_include_directories(Interp4Rotate PUBLIC ${CMAKE_SOURCE_DIR}/inc)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Interp4Rotate PRIVATE
        -fPIC
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wformat=2
        -Wunused
        -Wnull-dereference
        -Wconversion
        -Wno-unused-parameter
    )
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(Interp4Rotate PRIVATE /W4 /WX)
endif()

# #############################################################
# --- Wtyczka Interp4Pause  ---
# #############################################################
add_library(Interp4Pause SHARED 
  src/Interp4Pause.cpp
)

target_include_directories(Interp4Pause PUBLIC
  inc
  ${CMAKE_SOURCE_DIR}/inc
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Interp4Pause PRIVATE
        -fPIC
        -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wunused
        -Wnull-dereference -Wconversion -Wno-unused-parameter
    )
endif()


# #############################################################
# --- Wtyczka Interp4Set  ---
# #############################################################
add_library(Interp4Set SHARED 
  src/Interp4Set.cpp
)

target_include_directories(Interp4Set PUBLIC
  inc
  ${CMAKE_SOURCE_DIR}/inc
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Interp4Set PRIVATE
        -fPIC
        -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wunused
        -Wnull-dereference -Wconversion -Wno-unused-parameter
    )
endif()