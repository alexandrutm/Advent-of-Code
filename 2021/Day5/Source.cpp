#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct point
{
  int x;
  int y;
};

struct line
{
  point pointA;
  point pointB;
};

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

int CountOverlapPositions(const vector<vector<int>> & matrix)
{
  int count = 0;
  for (auto & line : matrix)
    for (auto element : line)
      if (element >= 2)
        count++;

  return count;
}

void ReadData(vector<line> & lines)
{
  ifstream fin("input.txt");
  string   lineStr;

  while (getline(fin, lineStr))
  {
    vector<int> valueLine;
    ParseStringToVectorInt(lineStr, valueLine);

    line newLine;
    newLine.pointA.x = valueLine[0];
    newLine.pointA.y = valueLine[1];
    newLine.pointB.x = valueLine[2];
    newLine.pointB.y = valueLine[3];

    lines.push_back(newLine);
  }
}

void BothParts()
{
  vector<line> lines;
  ReadData(lines);

  int x = 0;
  int y = 0;
  for (const auto & newLine : lines)
  {
    if (newLine.pointA.x > x)
    {
      x = newLine.pointA.x;
    }
    if (newLine.pointB.x > x)
    {
      x = newLine.pointB.x;
    }

    if (newLine.pointA.y > y)
    {
      y = newLine.pointA.y;
    }
    if (newLine.pointB.y > y)
    {
      y = newLine.pointB.y;
    }
  }

  vector<vector<int>> matrix;
  matrix.resize(x + 2, vector<int>(y + 3));

  for (const auto & line : lines)
  {
    int dx = line.pointA.x < line.pointB.x ? 1 : (line.pointA.x > line.pointB.x ? -1 : 0);
    int dy = line.pointA.y < line.pointB.y ? 1 : (line.pointA.y > line.pointB.y ? -1 : 0);

    if (dx == 0 || dy == 0)
    {
      for (int i = line.pointA.x, j = line.pointA.y;
           i != line.pointB.x + dx || j != line.pointB.y + dy; i += dx, j += dy)
      {
        matrix[j][i]++;
      }
    }
  }

  cout << "Part1 " << CountOverlapPositions(matrix);

  vector<vector<int>> matrix2;
  matrix2.resize(x + 2, vector<int>(y + 3));

  for (const auto & line : lines)
  {
    int dx = line.pointA.x < line.pointB.x ? 1 : (line.pointA.x > line.pointB.x ? -1 : 0);
    int dy = line.pointA.y < line.pointB.y ? 1 : (line.pointA.y > line.pointB.y ? -1 : 0);

    for (int i = line.pointA.x, j = line.pointA.y;
         i != line.pointB.x + dx || j != line.pointB.y + dy; i += dx, j += dy)

    {
      matrix2[j][i]++;
    }
  }
  cout << "\nPart2 " << CountOverlapPositions(matrix2);
}

int main()
{
  BothParts();
  return 0;
}
