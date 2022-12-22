#include <iostream>
#include <vector>
#include <string>
#include "../inc/fill_chart.h"
#include "../inc/write_file.h"
#include "../inc/read_file.h"
#include "../inc/print_vigenere.h"

using namespace std;

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
