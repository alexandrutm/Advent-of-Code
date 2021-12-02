#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define FORWARD "forward"
#define DOWN    "down"
#define UP      "up"

void ReadData(vector<string> & aData)
{
  ifstream fin("input.txt");
  string   currDir;

  while (getline(fin, currDir))
  {
    aData.push_back(currDir);
  }
}

void Part1(const vector<string> & aData)
{
  int horizontal = 0, depth = 0, depth2 = 0, aim = 0;

  for (auto instruction : aData)
  {
    stringstream ss;
    ss << instruction;

    string direction;
    int    value;

    ss >> direction;
    ss >> value;

    if (direction == FORWARD)
    {
      horizontal += value;
      depth2 += aim * value;
    }
    else if (direction == DOWN)
    {
      depth += value;
      aim += value;
    }
    else if (direction == UP)
    {
      depth -= value;
      aim -= value;
    }
  }
  cout << "part 1 = " << horizontal * depth;
  cout << "\npart 2 = " << horizontal * depth2;
}

int main()
{
  vector<string> data;

  ReadData(data);
  Part1(data);

  return 0;
}
