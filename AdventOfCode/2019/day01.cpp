#include "../lib.h"

void day1()
{
  ifstream fin("data.txt");
  string   line;
  int      sumP1 = 0;
  int      sumP2 = 0;

  while (!fin.eof())
  {
    int line;
    fin >> line;

    int firstSum = (floor(line / 3)) - 2;

    sumP1 += firstSum;
    sumP2 += firstSum;

    while (firstSum > 9)
    {
      int intermediarSum = (floor(firstSum / 3)) - 2;
      sumP2 += intermediarSum;
      firstSum = intermediarSum;
    }
  }

  cout << "First half: " << sumP1;
  cout << "\nSecond half: " << sumP2;
}
