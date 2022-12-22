#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../inc/write_file.h"
#include "../inc/no_illegal.h"
#include "../inc/encrypt_decrypt.h"

using namespace std;

int write_file(vector<char> &chart, string &message, string &key, string &shift_message, string &file_name)
{
  //setting flag for encryption
  bool encrypt = true;

  //file stream declared here
  ofstream file;
  
  //holds user choice in this function
  string choice;

  //menu header
  cout << "\033[2J\033[1;1H"; 
  cout << "Ultra, Super High Security, Encryption, Vigenere Cipher! by Team[JAK]" << endl;
  cout << "---------------------------------------------------------------------" << endl;
  cout << "ENCRYPTION MODE: write a new encrypted file." << endl;

  //enters name of file 
  cout << "\nEnter the name of the file (ESC + Enter to go back): ";
  getline(cin, file_name);

  //back button
  if (file_name[0] == 27)
    return 1;

  //attemps to open the file for the first time
  file.open(file_name);
 
  //if unable to open
  while (!file)
  {
    cout << "\nError: unable to create file." << endl;
    cout << "Make sure directory is not read only." << endl;
    cout << "Would you like to try again? No to return to main menu." << endl;
    cout << "Choice Y/N: ";
    getline(cin, choice);

    while (!((choice[0] == 'y') || (choice[0] == 'Y') || (choice[0] == 'n') || (choice[0] == 'N')))
    {
      cout << "\nYou did not make a valid choice." << endl;
      cout << "Please make a valid choice." << endl;
      cout << "Choice Y/N: ";
      getline(cin, choice);
    }

    if ((choice[0] == 'y') || (choice[0] == 'Y'))
    {
      cout << "\nEnter the name of the file (ESC + Enter to go back): ";
      getline(cin, file_name);

      //back button
      if (file_name[0] == 27)
        return 1;

      //tries to open file again
      file.open(file_name);
    }

    else
      return -1;
  }

  //enters message
  cout << "Enter message: ";
  getline(cin, message);

  //makes sure no weird keys were entered in message
  while (no_illegal(message))
  {
    cout << "\nYou entered an illegal key." << endl;
    cout << "Enter message: ";
    getline(cin, message);
  }

  //enters key
  cout << "Enter key: ";
  getline(cin, key);

  //makes sure no weird keys were entered in key
  while (no_illegal(key))
  {
    cout << "\nError: you entered an illegal key." << endl;
    cout << "Enter key: ";
    getline(cin, key);
  }
  
  //does encryption here
  encrypt_decrypt(chart, message, key, shift_message, encrypt); 
  
  //writes file
  file << "Encrypted message: " << shift_message;

  //closes file
  file.close();
  
  //letting user know file write was a success
  cout << "\nSuccess! The file was saved under the name: " << file_name << endl;

  //prompting user to run program again
  cout << "Return to main menu? No to exit program." << endl;
  cout << "Choice Y/N: ";
  getline(cin, choice);

  //user did not make valid choice
  while (!((choice[0] == 'y') || (choice[0] == 'Y') || (choice[0] == 'n') || (choice[0] == 'N')))
  {
    cout << "\nYou did not make a valid choice." << endl;
    cout << "Please make a valid choice." << endl;
    cout << "Choice Y/N: ";
    getline(cin, choice);
  }

  //runs program again
  if ((choice[0] == 'y') || (choice[0] == 'Y'))
    return 1;

  return 0;
}
