#include "../lib.h"
vector<vector<int>> grid;

enum direction
{
  up,
  down,
  leftL,
  rightL
};

bool CheckTillEdge(direction aDir, int aCol, int aLine, int value)
{
  switch (aDir)
  {
  case up:
    while (aLine > 0)
    {
      if (grid[aLine][aCol] > value)
        return false;
      aLine--;
    }
    break;
  case down:
    while (aLine < grid.size())
    {
      if (grid[aLine][aCol] > value)
        return false;

      aLine++;
    }
    break;
  case leftL:
    while (aCol < grid[aLine].size())
    {
      if (grid[aLine][aCol] > value)
        return false;

      aCol++;
    }
    break;
  case rightL:
    while (aCol > 0)
    {
      if (grid[aLine][aCol] > value)
        return false;

      aCol--;
    }
  default:
    break;
  }

  return true;
}

void day08()
{
  grid.resize(5);

  ifstream fin("data.txt");

  string line;
  int    m = 0;

  while (!fin.eof())
  {
    getline(fin, line);

    for (auto i : line)
      grid[m].push_back(i - '0');

    m++;
  }

  int visible = 16;

  for (int i = 1; i < grid.size() - 1; i++)
  {
    for (int j = 1; j < grid[i].size() - 1; j++)
    {
      if (CheckTillEdge(up, i, j, grid[i][j]) && CheckTillEdge(leftL, i, j, grid[i][j]) &&
          CheckTillEdge(down, i, j, grid[i][j]) && CheckTillEdge(rightL, i, j, grid[i][j]))
        visible++;
    }
  }
  cout << visible;
}

void main()
{
  day08();
}
