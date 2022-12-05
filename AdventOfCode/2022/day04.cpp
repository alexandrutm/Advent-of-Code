#include "../stdafx.h"

void day4()
{
  wifstream fin("data.txt");

  int firstHalf  = 0;
  int secondHalf = 0;

  while (!fin.eof())
  {
    wchar_t com, under;
    int     nr1, nr2, nr3, nr4;

    fin >> nr1 >> under >> nr2 >> com >> nr3 >> under >> nr4;

    if (nr1 <= nr3 && nr2 >= nr4)
      firstHalf++;
    else if (nr1 >= nr3 && nr2 <= nr4)
      firstHalf++;

    if (nr1 <= nr3 && nr2 >= nr3)
      secondHalf++;
    else if (nr1 >= nr3 && nr1 <= nr4)
      secondHalf++;
  }

  cout << "First: " << firstHalf;
  cout << "\nSecond: " << secondHalf;
}
