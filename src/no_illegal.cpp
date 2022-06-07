/*
checks that there is no weird
characters in program
at this point the string should already exist
*/

#include <string>
#include <vector>
#include "no_illegal.h"

using namespace std;

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
