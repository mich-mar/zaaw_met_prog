#include <iostream>
#include "wspolny_plik.hh"

using namespace std;

extern "C" {
  void Tool(const char* sText);
}


void Tool(const char* sText)
{
  cout << endl
       << TRESC_WSPOLNA << endl
       << " Komunikat funkcji z biblioteki Tool2" << endl
       << "       " << sText << endl
       << endl;
}
