#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void ReadData(vector<string> & aData)
{
  ifstream fin("input.txt");
  string   currDir;

  while (getline(fin, currDir))
  {
    aData.push_back(currDir);
  }
}

int Part2(vector<string> aData)
{
  vector<string> newData = aData;
  int            bit     = 0;
  while (newData.size() != 1)
  {
    // count
    int ones = 0, zeros = 0;

    for (auto number : newData)
    {
      for (int i = bit; i < number.size(); i++)
      {
        if (number[bit] == '1')
        {
          ones++;
        }
        else if (number[bit] == '0')
        {
          zeros++;
        }
      }
    }

    auto it = newData.begin();
    while (it != newData.end())
    {
      if (ones >= zeros)
      {
        // keep only number with bit 1
        if ((*it)[bit] == '0')
        {
          it = newData.erase(it);
        }
        else
          ++it;
      }
      else
      {
        // keep only number with bit 0
        if ((*it)[bit] == '1')
        {
          it = newData.erase(it);
        }
        else
          ++it;
      }
    }

    bit++;
  }

  vector<string> newData2 = aData;
  int            bit2     = 0;
  while (newData2.size() != 1)
  {
    // count
    int ones = 0, zeros = 0;

    for (auto number : newData2)
    {
      for (int i = bit2; i < number.size(); i++)
      {
        if (number[bit2] == '1')
        {
          ones++;
        }
        else if (number[bit2] == '0')
        {
          zeros++;
        }
      }
    }

    // delete from vector
    auto it = newData2.begin();
    while (it != newData2.end())
    {
      if (ones >= zeros)
      {
        // keep only number with bit 0
        if ((*it)[bit2] == '1')
        {
          it = newData2.erase(it);
        }
        else
          ++it;
      }
      else
      {
        // keep only number with bit 1
        if ((*it)[bit2] == '0')
        {
          it = newData2.erase(it);
        }
        else
          ++it;
      }
    }

    bit2++;
  }

  return stoi(newData.front(), nullptr, 2) * stoi(newData2.front(), nullptr, 2);
}

void Part1(const vector<string> & aData)
{
  string      gammaStr, epsilonStr;
  vector<int> countZeros;
  vector<int> countOnes;

  countOnes.resize(aData[0].size());
  countZeros.resize(aData[0].size());
  for (auto number : aData)
  {
    for (int bit = 0; bit < number.size(); bit++)
    {
      if (number[bit] == '1')
      {
        countOnes[bit]++;
      }
      else if (number[bit] == '0')
      {
        countZeros[bit]++;
      }
    }
  }

  for (int i = 0; i < countOnes.size(); i++)
  {
    if (countOnes[i] > countZeros[i])
    {
      gammaStr += '1';
      epsilonStr += '0';
    }
    else
    {
      gammaStr += '0';
      epsilonStr += '1';
    }
  }

  cout << "part 1 " << stoi(gammaStr, nullptr, 2) * stoi(epsilonStr, nullptr, 2);

  cout << "\nPart2 " << Part2(aData);
}

int main()
{
  vector<string> data;
  ReadData(data);
  Part1(data);
  return 0;
}
