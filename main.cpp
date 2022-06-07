/*
Vigenere Cipher with expanded
upper, lower case letters,
and special characters.

Team[JAK]

Class: CSC/CIS - 7
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

//prototyped functions
void fill_chart(vector<char> &);
bool no_illegal(string &);
void encrypt_decrypt(vector<char> &, string &, string &, string &, bool &);
int write_file(vector<char> &, string &, string &, string &, string &);
int read_file(vector<char> &, string &, string &, string &, string &);
int print_vigenere(vector<char> );

//main driver code
int main()
{
  //vector of characters to hold expanded vigenere chart
  //that includes upper/lower letters and special characters
  vector<char> chart;

  //strings hold the message, key, shifted message, and filename
  string message;
  string key;
  string shift_message;
  string file_name;

  //populates the vector of characters with the chart
  fill_chart(chart);

  //holds user choice in the menu
  string choice;

  //incase the program restarts
  bool run_program = false;

  //janky menu
  do
  {
    cout << "\033[2J\033[1;1H";
    cout << "Ultra, Super High Security, Encryption, Vigenere Cipher! by Team[JAK]" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1) Encryption" << endl;
    cout << "2) Decryption" << endl;
    cout << "3) Print Expanded Vigenere Cipher (Make sure to expand output window.)" << endl;
    cout << "4) Exit" << endl;
    cout << "Choice 1 - 4: ";
    getline(cin, choice);

    //user did not make valid choice
    while (!((choice[0] == '1') || (choice[0] == '2') || (choice[0] == '3') || (choice[0] == '4')))
    {
      cout << "\nYou did not make a valid choice." << endl;
      cout << "Please make a valid choice." << endl;
      cout << "Choice 1 - 4: ";
      getline(cin, choice);
    }

    //branching with encryption
    if (choice[0] == '1')
    {
      run_program = write_file(chart, message, key, shift_message, file_name);
      message.clear();
      key.clear();
      shift_message.clear();
      file_name.clear();
    }
    //branching wth decryption
    else if (choice[0] == '2')
    {
      run_program = read_file(chart, message, key, shift_message, file_name);
      message.clear();
      key.clear();
      shift_message.clear();
      file_name.clear();
    }

    else if (choice[0] == '3')
      run_program = print_vigenere(chart);

    //exits menu
    else
      run_program = false;

  } while(run_program);

  message.clear();
  key.clear();
  shift_message.clear();
  file_name.clear();

  //exit message
  cout << "\033[2J\033[1;1H";
  cout << "Thanks for using the program! :)" << endl;
  return 0;
}

//writes an encrypted file here
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

//reads in a file and decrypts here
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

//decrypts/decrypts message here
void encrypt_decrypt(vector<char> &chart, string &message, string &key, string &shift_message, bool &encrypt)
{
  //vectors to hold casted message, key, and shifted message
  //into integers for easy comparison of the new positions
  //of ascii letters and special character in the expanded chart
  vector<int> cast_message;
  vector<int> cast_key;
  vector<int> cast_shift_message;

  //if the key is longer than the message
  if (key.size() > message.size())
    key.resize(message.size());
 
  //if the key is shorter than the message
  else if (key.size() < message.size())
  {
    //stores the difference of message and key size
    int diff = (message.size() - key.size());

    //makes key the same size of message
    for (int i = 0; i < diff; i++)
      key.push_back(key[i]);
  }

  //casts message into ints to be used with
  //new assigned value of ascii table 0 - 95
  for (int i = 0; i < message.size(); i++)
  {
    for (int j = 0; j < chart.size(); j++)
    {
      if (message[i] == chart[j])
       cast_message.push_back(j); 
    }
  }

  //casts key into ints to be used with
  //new assigned value of ascii table 0 - 95
  for (int i = 0; i < key.size(); i++)
  {
    for (int j = 0; j < chart.size(); j++)
    {
      if (key[i] == chart[j])
       cast_key.push_back(j); 
    }
  }
  
  //does encryption (note chart.size() = 95)
  if (encrypt)
  {
    for (int i = 0; i < message.size(); i++)
     cast_shift_message.push_back((cast_message[i] + cast_key[i]) % chart.size());
  }

  //does decryption (note chart.size() = 95)
  else
  {
    for (int i = 0; i < message.size(); i++)
     cast_shift_message.push_back(((cast_message[i] - cast_key[i]) + chart.size()) % chart.size());
  }

  //finally exports the proper characters to a string
  for (int i = 0; i < cast_shift_message.size(); i++)
  {
    for (int j = 0; j < chart.size(); j++)
    {
      if (cast_shift_message[i] == j)
        shift_message.push_back(chart[j]);
    }
  }
}

//fills in the expanded vigenere cipher
void fill_chart(vector<char> &chart)
{
  //fills in chart with ascii 'A' to 'Z'
  for (int i = 'A'; i <= 'Z'; i++)
    chart.push_back(i);
  
  //fills in chart with ascii 'a' to 'z'
  for (int i = 'a'; i <= 'z'; i++)
    chart.push_back(i);

  //fills in chart with ascii ' ' to '@'
  for (int i = ' '; i <= '@'; i++)
    chart.push_back(i);

  //fills in chart with ascii '[' to '`'
  for (int i = '['; i <= '`'; i++)
    chart.push_back(i);

  //fills in chart with ascii '{' to '~'
  for (int i = '{'; i <= '~'; i++)
    chart.push_back(i);
}

//illegal characters are found here
bool no_illegal(string &string_check)
{
  //finds if there is weird character/s
  for (int i = 0; i < string_check.size(); i++)
  {
    if (string_check[i] > '~' || string_check[i] < ' ')
      return true;
  }

  return false;
}

//prints out the vigenere
int print_vigenere(vector<char> chart)
{
  //holds user choice
  string choice;

  //clears output window
  cout << "\033[2J\033[1;1H";

  //print out the top cipher bar
  cout << "     ";
  for (int i = 0; i < chart.size(); i++)
    cout << chart[i] << " ";

  //space required for proper output
  cout << endl;
  cout << "     ";

  //prints out the divider 
  for (int i = 0; i < 189; i++)
    cout << "-";

  //new lines required for proper output
  cout << endl;
  cout << endl;

  //prints out the left hand bar of the cipher
  //and first cipher line
  cout << "A|   ";
  for (int i = 0; i < chart.size(); i++)
    cout << chart[i] << " ";
  
  //new line required for proper output
  cout << endl;


  //prints out the other remainding lines
  for (int i = 0; i < 94; i++)
  {
    rotate(chart.begin(), chart.begin() + 1, chart.end());

    cout << chart[0] << "|   ";

    for (int i = 0; i < chart.size(); i++)
     cout << chart[i] << " ";

    cout << endl;
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
    cout << "Choice Y/N: ";
    getline(cin, choice);
  }

  //runs program again
  if ((choice[0] == 'y') || (choice[0] == 'Y'))
    return 1;

  return 0;
}
