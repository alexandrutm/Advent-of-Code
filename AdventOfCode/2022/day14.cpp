#include "../lib.h"

struct point
{
  int x, y;
};

struct wall
{
  point start, end;
};

void ExtractSignedInts(string s, vector<point> & aNumbers)
{
  regex rx("\\d+");

  smatch match;

  auto words_begin = sregex_iterator(s.begin(), s.end(), rx);
  auto words_end   = sregex_iterator();

  for (auto i = words_begin; i != words_end; ++i)
  {
    smatch match = *i;
    int    x     = stoi(match.str());

    ++i;
    match = *i;
    int y = stoi(match.str());

    aNumbers.push_back(point(x, y));
  }
}

void SetWall(point p1, point p2, vector<vector<char>> & cave)
{
  int minX = min(p1.x, p2.x);
  int maxX = max(p1.x, p2.x);

  int minY = min(p1.y, p2.y);
  int maxY = max(p1.y, p2.y);

  for (int i = minX; i <= maxX; i++)
  {
    for (int j = minY; j <= maxY; j++)
    {
      cave[j][i] = '#';
    }
  }
}

void day14()
{
  ifstream fin("data.txt");

  string inputLine;

  vector<vector<char>> cave(1000, vector<char>(1000, '.'));

  int highestY = 0;

  while (!fin.eof())
  {
    getline(fin, inputLine);
    vector<point> coord;

    ExtractSignedInts(inputLine, coord);

    for (int i = 0; i < coord.size() - 1; i++)
    {
      if (coord[i].y > highestY)
        highestY = coord[i].y;

      if (coord[i + 1].y > highestY)
        highestY = coord[i].y;

      SetWall(coord[i], coord[i + 1], cave);
    }
  }

  bool full = false;

  int sandUnits = 0;

  highestY += 2;

  for (int i = 0; i < cave[0].size(); i++)
  {
    cave[highestY][i] = '#';
  }

  while (!full)
  {
    point currentSand(500, 0);

    if (cave[currentSand.y][currentSand.x] == 'o')
      break;

    sandUnits++;

    // drop sand
    while (cave[currentSand.y + 1][currentSand.x] != '#' &&
           cave[currentSand.y + 1][currentSand.x] != 'o')
    {
      currentSand.y++;

      if (currentSand.y == 999)
      {
        full = true;
        break;
      }
    }

    if (!full && cave[currentSand.y + 1][currentSand.x] == '#')
    {
      cave[currentSand.y][currentSand.x] = 'o';
      continue;
    }
    else if (!full && cave[currentSand.y + 1][currentSand.x] == 'o')
    {
      bool positioned = false;
      while (1)
      {
        if (cave[currentSand.y + 1][currentSand.x] == '.')
        {
          currentSand.y++;

          if (currentSand.y == 999)
          {
            full = true;
            break;
          }
        }  // check one step down and to the left
        else if (cave[currentSand.y + 1][currentSand.x - 1] == '.')
        {
          currentSand.y += 1;
          currentSand.x -= 1;

          if (currentSand.y == 999 || currentSand.x == 0)
          {
            full = true;
            break;
          }

          continue;
        }  // check one step down and to the right
        else if (cave[currentSand.y + 1][currentSand.x + 1] == '.')
        {
          currentSand.x += 1;
          currentSand.y += 1;

          if (currentSand.x == 999 || currentSand.y == 999)
          {
            full = true;
            break;
          }

          continue;
        }
        else
        {
          cave[currentSand.y][currentSand.x] = 'o';
          break;
        }
      }
    }
  }

  cout << sandUnits - 1;
}
