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
 
 string input;

 string user;
 string passwd;
 string new_passwd;

 cout << "Enter preferred hash table capacity : "; 
 getline(cin, input);

 size_t size = size_t(atoi(input.c_str()));
 PassServer ps(size);
 
 cout << input << endl;
 while(1)
 {
    Menu();
    getline(cin, input);
    

    if(input == "l")
    {
      cout << "Enter password file name to load from : ";
      getline(cin, input); 
      ps.load(input.c_str());
    }

    if(input == "a")
    {
      cout << "Enter username : ";
      getline(cin, user); 
      cout << "Enter password : ";
      getline(cin, passwd); 
      if(ps.addUser(make_pair(user, passwd)))
        cout << "\nUser " << user << " added.";
      else
        cout << "\nUser " << user << " already exists!";
    }

    if(input == "r")
    {
      cout << "Enter username : ";
      getline(cin, user);
      if(ps.removeUser(user))
        cout << "User " << user << " deleted.";
      else
        cout << "*****Error: User not found. Could not delete user";
    }

    if(input == "c")
    {
      cout << "Enter username : ";
      getline(cin, user); 
      cout << "Enter password : ";
      getline(cin, passwd); 

      cout << "\nEnter new password : ";
      getline(cin, new_passwd); 

      if(ps.changePassword(make_pair(user, passwd), new_passwd))
        cout << "\nPassword changed for user " << user;
      else
        cout << "\nError: could not change user password";
    }

    if(input == "f")
    {
      cout << "Enter username : ";
      getline(cin, user);
      if(ps.find(user))
        cout << "\nUser '" << user << "' found.";
      else
        cout << "\nUser '" << user << "' not found.";
    }

    if(input == "d")
    {
      ps.dump();
    }

    if(input == "s")
      cout << "Size of hashtable: " << ps.size();

    if(input == "w")
    {
      cout << "Enter password file name to write to : ";
      getline(cin, input); 
      ps.write_to_file(input.c_str());
    }  

    if(input == "x")
      break;
 }
}