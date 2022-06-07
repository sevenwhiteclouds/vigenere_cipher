#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "read_file.h"
#include "no_illegal.h"
#include "encrypt_decrypt.h"

using namespace std;

int read_file(vector<char> &chart, string &message, string &key, string &shift_message, string &file_name)
{
  //setting flag for decryption
  bool encrypt = false;

  //file stream declared here
  ifstream file;

  //holds user choice in this function
  string choice;

  //menu header
  cout << "\033[2J\033[1;1H";
  cout << "Ultra, Super High Security, Encryption, Vigenere Cipher! by Team[JAK]" << endl;
  cout << "---------------------------------------------------------------------" << endl;
  cout << "DECRYPTION MODE: read and decrypt a message from a file." << endl;

  //captures name of the file
  cout << "\nEnter the name of the file (ESC + Enter to go back): ";
  getline(cin, file_name);

  //back button
  if (file_name[0] == 27)
    return 1;

  //attempt to open file for the first time here
  file.open(file_name);

  //if file was not able to open
  while (!file)
  {
    cout << "\nError: unable to read file." << endl;
    cout << "Make sure file exists in the directory and is accessible." << endl;
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

  //reads in the file content while ignore the first 19 characters and stores into a string
  file.ignore(19);
  getline(file, message);
  
  //reads in key from user
  cout << "Enter key: ";
  getline(cin, key);

  //make sure not weird keys were entered in key
  while (no_illegal(key))
  {
    cout << "\nError: you entered an illegal key." << endl;
    cout << "Enter key: ";
    getline(cin, key);
  }

  //does decryption here
  encrypt_decrypt(chart, message, key, shift_message, encrypt); 

  //shows user encrypted message and now decrypted message
  cout << "\nKey used         : " << key << endl;
  cout << "Encrypted message: " << message << endl;
  cout << "\nDecrypted message: " << shift_message << endl;

  //ask user if write decrypted message to file
  cout << "\nWould you like to write the decrypted message to the file?" << endl; 
  cout << "Choice Y/N: ";
  getline(cin, choice);
      
  //make sure user makes right choice
  while (!((choice[0] == 'y') || (choice[0] == 'Y') || (choice[0] == 'n') || (choice[0] == 'N')))
  {
    cout << "\nYou did not make a valid choice." << endl;
    cout << "Please make a valid choice." << endl;
    cout << "Choice Y/N: ";
    getline(cin, choice);
  }

  if ((choice[0] == 'y') || (choice[0] == 'Y'))
  {
    //ofstream to write to file
    ofstream file;
    file.open(file_name);

    //if unable to write to file
    if (!file)
    {
      cout << "Error: unable to write to file" << endl;
      cout << "Make sure directory/file is not read only." << endl;
    }

    //writes to file
    else
    {
      file << "Encrypted message: " << message << endl;
      file << "Decrypted message: " << shift_message; 
      cout << "\nSuccess! The file has been updated and saved with the decrypted message." << endl;
    }
  }

  //prompting user to run program again
  cout << "\nReturn to main menu? No to exit program." << endl;
  cout << "Choice Y/N: ";
  getline(cin, choice);

  //user did not make valid choice
  while (!((choice[0] == 'y') || (choice[0] == 'Y') || (choice[0] == 'n') || (choice[0] == 'N')))
  {
    cout << "\nYou did not make a valid choice." << endl;
    cout << "Please make a valid choice." << endl;
    cout << "choice y/N: ";
    getline(cin, choice);
  }

  //runs program again
  if ((choice[0] == 'y') || (choice[0] == 'Y'))
    return 1;

  return 0;
}
