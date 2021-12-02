#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void ReadData(vector<int> & aData)
{
  ifstream fin("part1.txt");

  int curr;
  while (fin >> curr)
  {
    aData.push_back(curr);
  }
}

void Part1(const vector<int> & aData)
{
  int prev, count;
  count = 0;
  prev  = aData.front();

  for (auto curr : aData)
  {
    curr > prev ? count++ : 0;
    prev = curr;
  }

  cout << count << "\n";
}

void Part2(const vector<int> & aData)
{
  vector<int> aSums;

  for (int i = 0; i < aData.size() - 2; i++)
  {
    int sum = 0;
    for (int j = i; j < i + 3; j++)
    {
      sum += aData[j];
    }
    aSums.push_back(sum);
  }

  Part1(aSums);
}

int main()
{
  vector<int> data;

  ReadData(data);

  Part1(data);
  Part2(data);

  return 0;
}
