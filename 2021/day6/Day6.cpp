#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define NEWLANTERNFISH 8
#define NEWLIFE        6

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

void SimulateLanternFish(const vector<int> & initialState)
{
  vector<int> lanternFishGroup = initialState;

  for (int i = 0; i < 256; i++)
  {
    int newfish = 0;

    for (int j = 0; j < lanternFishGroup.size(); j++)
    {
      if (lanternFishGroup[j] == 0)
      {
        newfish++;
        lanternFishGroup[j] = NEWLIFE;
      }
      else
        lanternFishGroup[j] -= 1;
    }

    for (int j = 0; j < newfish; j++)
    {
      lanternFishGroup.push_back(NEWLANTERNFISH);
    }
  }

  cout << "Part1 " << lanternFishGroup.size();
}

void SolutionDay6()
{
  vector<int> lanternFishGroup;

  ifstream fin("inputday6.txt");
  string   str;

  fin >> str;
  ParseStringToVectorInt(str, lanternFishGroup);
  SimulateLanternFish(lanternFishGroup);
}

int main()
{
  SolutionDay6();
}
