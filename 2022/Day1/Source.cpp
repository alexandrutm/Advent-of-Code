#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int main()
{
  ifstream fin("day1.txt");

  string currentcarry;
  int    currCarry = 0;

  vector<int> elfsLoad;

  while (!fin.eof())
  {
    getline(fin, currentcarry);

    if (currentcarry == "")
    {
      elfsLoad.push_back(currCarry);
      currCarry = 0;
      continue;
    }

    currCarry += stoi(currentcarry);
  }

  cout << "Highest calories " << *(max_element(elfsLoad.begin(), elfsLoad.end()));

  sort(elfsLoad.begin(), elfsLoad.end(), greater<int>());

  cout << "\n Total of most 3 carriers "
       << std::accumulate(elfsLoad.begin(), elfsLoad.begin() + 3, 0);

  return 0;
}
