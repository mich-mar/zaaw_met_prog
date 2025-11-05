#include <iostream>
#include <dlfcn.h>

#include "module1.hh"
#include "module2.hh"
using namespace std;



bool TestBiblioteki(const char* sNazwaBiblioteki)
{
  void *pLibHnd = dlopen(sNazwaBiblioteki,RTLD_LAZY);
  if (!pLibHnd) {
    cerr << dlerror() << endl;
    return false;
  }

  void (*pFun)(const char*) 
            = reinterpret_cast<void (*)(const char*)>(dlsym(pLibHnd,"Tool"));

  if (!pFun) {
    cerr << dlerror() << endl;
    dlclose(pLibHnd);
    return false;
  }

  pFun("Wywolanie funkcji w programie.");
  dlclose(pLibHnd);
  return true;
}



#define LIB_TEST( NazwaBiblioteki ) \
  if (!TestBiblioteki(NazwaBiblioteki)) {                                     \
      cout << ":(  Test biblioteki \"" NazwaBiblioteki "\" nie powiodl sie."; \
  } else {                                                                    \
      cout << ":)  Test biblioteki \"" NazwaBiblioteki "\" zakonczony powodzeniem."; \
  }                                                                           \
  cout << endl;



int main()
{
  cout << "Interpreter polecen" << endl;
  Fun1("Wywolanie funkcji nr 1");
  Fun2("Wywolanie funkcji nr 2");

  LIB_TEST("libtool1.so");
  LIB_TEST("libtool2.so");  
}
