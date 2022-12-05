#include "../stdafx.h"

void day1()
{
  ifstream fin("day1.txt");

  string currentCalories;
  int    totalCaloriesElf = 0;

  vector<int> elfsLoad;

  while (!fin.eof())
  {
    getline(fin, currentCalories);

    if (currentCalories == "")
    {
      elfsLoad.push_back(totalCaloriesElf);
      totalCaloriesElf = 0;
      continue;
    }

    totalCaloriesElf += stoi(currentCalories);
  }

  cout << "Highest calories " << *(max_element(elfsLoad.begin(), elfsLoad.end()));

  sort(elfsLoad.begin(), elfsLoad.end(), greater<int>());

  cout << "\n Total of most 3 carriers "
       << std::accumulate(elfsLoad.begin(), elfsLoad.begin() + 3, 0);
}
