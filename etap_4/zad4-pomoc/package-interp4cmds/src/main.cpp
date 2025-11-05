#include <iostream>
#include <dlfcn.h>

#include "module1.hh"
#include "module2.hh"
using namespace std;

int main()
{
  cout << "Interpreter polecen" << endl;
  Fun1("Wywolanie funkcji nr 1");
  Fun1("Wywolanie funkcji nr 2");

  void *pLibHnd = dlopen("libtool.so",RTLD_LAZY);
  if (!pLibHnd) {
    cerr << dlerror() << endl;
    return 1;
  }

  void (*pFun)(const char*) 
            = reinterpret_cast<void (*)(const char*)>(dlsym(pLibHnd,"Tool"));

  if (!pFun) {
    cerr << dlerror() << endl;
    dlclose(pLibHnd);
    return 1;
  }

  pFun("Wywolanie funkcji w programie.");
  dlclose(pLibHnd);
}
