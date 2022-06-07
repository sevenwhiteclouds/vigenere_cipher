#include <string>
#include <vector>
#include "encrypt_decrypt.h"

using namespace std;

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
