#include <iostream>

using namespace std;

extern "C" {
  void Tool(const char* sText);
}


void Tool(const char* sText)
{
  cout << endl
       << " Komunikat funkcji z biblioteki Tool" << endl
       << "       " << sText << endl
       << endl;
}
