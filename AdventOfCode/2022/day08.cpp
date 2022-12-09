#include "../lib.h"

vector<vector<int>> grid;
enum direction
{
  up,
  down,
  leftL,
  rightL
};
int CheckTillEdge(direction aDir, int aCol, int aLine, int value)
{
  int currentView = 0;
  switch (aDir)
  {
  case up:
    while (aLine >= 0)
    {
      currentView += 1;
      if (grid[aLine][aCol] >= value)
        return currentView;
      // return false
      aLine--;
    }
    break;
  case down:
    while (aLine < grid.size())
    {
      currentView += 1;
      if (grid[aLine][aCol] >= value)
        return currentView;
      // return false
      aLine++;
    }
    break;
  case leftL:
    while (aCol >= 0)
    {
      currentView += 1;
      if (grid[aLine][aCol] >= value)
        return currentView;  // return false
      aCol--;
    }
    break;
  case rightL:
    while (aCol < grid[aLine].size())
    {
      currentView += 1;
      if (grid[aLine][aCol] >= value)
        return currentView;
      // return false;
      aCol++;
    }
  default:
    break;
  }
  return currentView;
  // return true;
}
void day08()
{
  grid.resize(99);
  ifstream fin("data.txt");
  string   line;
  int      m = 0;
  while (!fin.eof())
  {
    getline(fin, line);
    for (auto i : line)
      grid[m].push_back(i - '0');
    m++;
  }
  //  int visible = 0;
  // for (int i = 1; i < grid.size() - 1; i++)
  //    for (int j = 1; j < grid[i].size() - 1; j++)
  //      {
  //          if (CheckTillEdge(up, j, i - 1, grid[i][j]) || CheckTillEdge(leftL, j - 1, i,
  //          grid[i][j]) ||
  //              CheckTillEdge(down, j, i + 1, grid[i][j]) || CheckTillEdge(rightL, j + 1, i,
  //              grid[i][j])) visible++;
  //      }
  // std::cout << visible;

  int maxViewScene = 0;
  for (int i = 1; i < grid.size() - 1; i++)
    for (int j = 1; j < grid[i].size() - 1; j++)
    {
      int currentViewScene = 1;
      currentViewScene *= CheckTillEdge(up, j, i - 1, grid[i][j]);
      currentViewScene *= CheckTillEdge(leftL, j - 1, i, grid[i][j]);
      currentViewScene *= CheckTillEdge(down, j, i + 1, grid[i][j]);
      currentViewScene *= CheckTillEdge(rightL, j + 1, i, grid[i][j]);
      if (maxViewScene < currentViewScene)
        maxViewScene = currentViewScene;
    }

  cout << "\nSecondHalf: " << maxViewScene;
}
