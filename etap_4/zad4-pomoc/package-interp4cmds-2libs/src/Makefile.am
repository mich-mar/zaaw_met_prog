bin_PROGRAMS=interp4cmds
interp4cmds_SOURCES = main.cpp \
                     module1.cpp \
                     module2.cpp
interp4cmds_CXXFLAGS = -I../inc -I../../../inc -std=c++17
interp4cmds_LDFLAGS = -Wl,-rpath='$(libdir)' ${LIB_DLOPEN} -lxerces-c
