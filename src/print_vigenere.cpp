#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "print_vigenere.h"

using namespace std;

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
