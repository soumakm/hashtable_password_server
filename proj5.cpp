#include <iostream>
#include "passserver.h"


using namespace std;

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main() {

 string size_str = "0";
 cout << "Enter preferred hash table capacity: "; 
 getline(cin, size_str);

 size_t size = size_t(atoi(size_str.c_str()));
 PassServer ps(size);
 
 cout << size_str << endl;

 Menu();
}