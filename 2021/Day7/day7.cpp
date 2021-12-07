#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void ParseStringToVectorInt(const string & str, vector<int> & result)
{
  typedef regex_iterator<std::string::const_iterator> re_iterator;
  typedef re_iterator::value_type                     re_iterated;

  regex re("(\\d+)");

  re_iterator rit(str.begin(), str.end(), re);
  re_iterator rend;

  transform(rit, rend, std::back_inserter(result),
            [](const re_iterated & it)
            {
              return std::stoi(it[1]);
            });
}

int GetLeastFuel(int aPos, const vector<int> aCrabs)
{
  int count = 0;
  for (auto crab : aCrabs)
  {
    int fuel     = 0;
    int distance = abs(crab - aPos);
    for (int i = 0; i < distance; i++)
    {
      fuel += (i + 1);
    }
    count += fuel;
  }
  return count;
}

void SolutionDay7()
{
  vector<int> crabs;

  ifstream fin("input.txt");
  string   str;

  fin >> str;
  ParseStringToVectorInt(str, crabs);

  int leastFuel = 999999999;

  int maxElem = *max_element(std::begin(crabs), std::end(crabs));

  for (int pos = 0; pos < maxElem; pos++)
  {
    int fuel = GetLeastFuel(pos, crabs);
    if (leastFuel > fuel)
    {
      leastFuel = fuel;
    }
  }
  cout << "Part1 " << leastFuel;
}

void main()
{
  SolutionDay7();
}
