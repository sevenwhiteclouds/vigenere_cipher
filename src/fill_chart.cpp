#include <vector>
#include <string>
#include "fill_chart.h"

using namespace std;

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
