#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
  ifstream fin("day1.txt");

  string currentcarry;
  int    currCarry = 0;
  int    mostCarry = 0;

  vector<int> allCarry;

  while (!fin.eof())
  {
    getline(fin, currentcarry);

    if (currentcarry == "")
    {
      if (currCarry > mostCarry)
        mostCarry = currCarry;

      allCarry.push_back(currCarry);
      currCarry = 0;
      continue;
    }

    currCarry += stoi(currentcarry);
  }

  cout << mostCarry;

  sort(allCarry.begin(), allCarry.end(), greater<int>());

  cout << "\n Total of most 3 carriers "
       << std::accumulate(allCarry.begin(), allCarry.begin() + 3, 0);

  return 0;
}