#include "../lib.h"

void day12()
{
  ifstream fin("data.txt");

  vector<string> graph;
  string         line;

  while (fin >> line)
    graph.push_back(line);

  int nrRow = graph.size();
  int nrCol = graph[0].size();

  pair<int, int> start = { -1, -1 }, end = { -1, -1 };

  F0R(i, nrRow)
  F0R(j, nrCol)
  {
    if (graph[i][j] == 'S')
    {
      start = { i, j };
      // p1
      // graph[i][j] = 'a'-1;

      // p2
      graph[i][j] = 'a';
    }
    if (graph[i][j] == 'E')
    {
      end = { i, j };

      graph[i][j] = 'z' + 1;
    }
  }

  vector<vector<int>>   dist(nrRow, vector<int>(nrCol, std::numeric_limits<int>::max()));
  queue<pair<int, int>> verts;

  verts.push(start);
  dist[start.first][start.second] = 0;

  // p2
  F0R(i, nrRow)
  F0R(j, nrCol)
  {
    if (graph[i][j] == 'a')
    {
      verts.push({ i, j });
      dist[i][j] = 0;
    }
  }

  while (!verts.empty())
  {
    auto currentVert = verts.front();
    verts.pop();

    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { 1, 0, -1, 0 };

    F0R(k, 4)
    {
      int neighbourI = currentVert.first + dx[k];
      int neighbourJ = currentVert.second + dy[k];

      if (0 <= neighbourI && neighbourI < nrRow && 0 <= neighbourJ && neighbourJ < nrCol)
        if (graph[neighbourI][neighbourJ] <= graph[currentVert.first][currentVert.second] + 1 &&
            dist[neighbourI][neighbourJ] > dist[currentVert.first][currentVert.second] + 1)
        {
          dist[neighbourI][neighbourJ] = dist[currentVert.first][currentVert.second] + 1;
          verts.push({ neighbourI, neighbourJ });
        }
    }
  }

  cout << dist[end.first][end.second] << '\n';
}
