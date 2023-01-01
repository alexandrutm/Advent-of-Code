#include "../lib.h"

int main()
{
  ifstream fin("data.txt");

  vector<ll> digitsBase5;

  while (!fin.eof())
  {
    string line;
    getline(fin, line);

    for (int i = line.length() - 1; i >= 0; --i)
    {
      int digit;

      if (line[i] == '-')
      {
        digit = -1;
      }
      else if (line[i] == '=')
      {
        digit = -2;
      }
      else
      {
        digit = line[i] - '0';
      }

      int digitIndex = line.length() - 1 - i;

      if (digitIndex >= digitsBase5.size())
      {
        digitsBase5.push_back(digit);
      }
      else
      {
        while (true)
        {
          if (digitIndex >= digitsBase5.size())
          {
            digitsBase5.push_back(0);
          }

          int newVal = digitsBase5[digitIndex] + digit;

          if (newVal > 2)
          {
            digitsBase5[digitIndex] = newVal - 5;
            digit                   = 1;

            ++digitIndex;
          }
          else if (newVal < -2)
          {
            digitsBase5[digitIndex] = 5 + newVal;
            digit                   = -1;

            ++digitIndex;
          }
          else
          {
            digitsBase5[digitIndex] = newVal;
            break;
          }
        }
      }
    }
  }

  while (!digitsBase5.empty() && digitsBase5.back() == 0)
  {
    digitsBase5.pop_back();
  }

  for (int i = digitsBase5.size() - 1; i >= 0; --i)
  {
    if (digitsBase5[i] == -1)
    {
      cout << '-';
    }
    else if (digitsBase5[i] == -2)
    {
      cout << '=';
    }
    else
    {
      cout << digitsBase5[i];
    }
  }
}
