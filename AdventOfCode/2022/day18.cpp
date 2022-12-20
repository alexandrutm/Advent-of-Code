#include "../lib.h"

void ExtractInts(string s, vector<int> & aNumbers)
{
  std::regex rx("-?\\d+");

  std::smatch match;

  auto words_begin = sregex_iterator(s.begin(), s.end(), rx);
  auto words_end   = sregex_iterator();

  for (auto i = words_begin; i != words_end; ++i)
  {
    smatch match = *i;
    int    x     = stoi(match.str());

    aNumbers.push_back(x);
  }
}

void day18()
{
  ifstream fin("data.txt");
  string   line;

  set<vector<int>> allCubes;
  while (getline(fin, line))
  {
    vector<int> cube;
    ExtractInts(line, cube);

    allCubes.insert(cube);
  }

  // p1
  int surfaceArea = 0;
  for (auto cube : allCubes)
  {
    for (int axis = 0; axis < 3; ++axis)
    {
      for (int d = -1; d <= 1; d += 2)
      {
        vector<int> q = cube;
        q[axis] += d;

        if (allCubes.count(q) == 0)
          ++surfaceArea;
      }
    }
  }

  cout << surfaceArea << endl;

  // p2
  vector<int> cubesMin(3, INT_MAX), cubesMax(3, INT_MIN);

  for (auto cube : allCubes)
  {
    for (int axis = 0; axis < 3; ++axis)
    {
      cubesMin[axis] = min(cubesMin[axis], cube[axis]);
      cubesMax[axis] = max(cubesMax[axis], cube[axis]);
    }
  }

  for (int axis = 0; axis < 3; ++axis)
  {
    --cubesMin[axis];
    ++cubesMax[axis];
  }

  vector<vector<int>> stack = { cubesMin };
  set<vector<int>>    visited;
  surfaceArea = 0;

  while (!stack.empty())
  {
    auto cube = stack.back();
    stack.pop_back();
    if (visited.count(cube))
      continue;
    visited.insert(cube);
    for (int axis = 0; axis < 3; ++axis)
    {
      for (int d = -1; d <= 1; d += 2)
      {
        vector<int> q = cube;
        q[axis] += d;
        if (allCubes.count(q))
          ++surfaceArea;
        if (allCubes.count(q) == 0 && visited.count(q) == 0)
        {
          bool ok = true;
          for (int axis = 0; axis < 3; ++axis)
          {
            if (q[axis] < cubesMin[axis] || q[axis] > cubesMax[axis])
            {
              ok = false;
              break;
            }
          }
          if (ok)
            stack.push_back(q);
        }
      }
    }
  }
  cout << surfaceArea << endl;
}
