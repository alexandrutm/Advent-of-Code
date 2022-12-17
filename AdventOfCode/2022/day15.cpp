#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

using namespace std;

struct point
{
  int x, y;
};

struct senzor
{
  point Pos;

  set<pair<int, int>> detectedPositions;
};

int distanceManh(point a, point b)
{
  return abs(a.x - b.x) + abs(a.y - b.y);
}

void ExtractSignedlong(string s, vector<point> & aNumbers)
{
  std::regex rx("-?\\d+");

  std::smatch match;

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

void main()
{
  ifstream fin("data.txt");

  string inputLine;

  vector<pair<senzor, point>> senzorBeacons;

  int highestY = 0;

  while (!fin.eof())
  {
    getline(fin, inputLine);
    vector<point> coord;

    ExtractSignedlong(inputLine, coord);

    senzor sen;
    sen.Pos = coord[0];

    senzorBeacons.push_back(make_pair(sen, coord[1]));
  }

  /*
  *
  * p1
  int yMAX = 2000000;

  for (auto & senzorBeacon : senzorBeacons)
  {
    // get dist to c
    auto distManh = distanceManh(senzorBeacon.first.Pos, senzorBeacon.second);

    // mark all positions from senzor + dist as detected
    int senzorPosX = senzorBeacon.first.Pos.x;
    int senzorPosY = senzorBeacon.first.Pos.y;

    if (senzorPosY < yMAX)
    {
      for (int currentY = senzorPosY; currentY <= senzorPosY + distManh; currentY++)
      {
        if (currentY == yMAX)
        {
          int distX = (senzorPosY + distManh) - currentY;

          for (int x = senzorPosX - distX; x <= senzorPosX + distX; x++)
          {
            senzorBeacon.first.detectedPositions.insert(make_pair(x, currentY));
          }
        }
      }
    }
    else if (senzorPosY > yMAX)
    {
      for (int currentY = senzorPosY; currentY >= senzorPosY - distManh; currentY--)
      {
        if (currentY == yMAX)
        {
          int distX = (currentY + distManh) - senzorPosY;

          for (int x = senzorPosX - distX; x <= senzorPosX + distX; x++)
          {
            senzorBeacon.first.detectedPositions.insert(make_pair(x, currentY));
          }
        }
      }
    }
    else
    {
      for (int x = senzorPosX - distManh; x <= senzorPosX + distManh; x++)
      {
        senzorBeacon.first.detectedPositions.insert(make_pair(x, senzorPosY));
      }
    }
  }

  set<pair<int, int>> positions;

  for (auto senzorBeacon : senzorBeacons)
  {
    for (auto pos : senzorBeacon.first.detectedPositions)
    {
      positions.insert(make_pair(pos.first, pos.second));
    }
  }

  set<int> nrBeacons;

  for (auto senzorBeacon : senzorBeacons)
  {
    auto found = positions.find(make_pair(senzorBeacon.second.x, senzorBeacon.second.y));

    if (found != positions.end())
      nrBeacons.insert(senzorBeacon.second.x);
  }

  cout << positions.size() - nrBeacons.size();
  */

  // p2
  for (int y = 0; y <= 4000000; y++)
  {
    vector<pair<long long, long long>> ranges;

    for (auto & s : senzorBeacons)
    {
      auto distManh = distanceManh(s.first.Pos, s.second);

      auto & coords = s.first.Pos;
      int    side   = distManh - abs(coords.y - y);

      if (side < 0)
        continue;

      ranges.emplace_back(coords.x - side, coords.x + side);
    }

    sort(ranges.begin(), ranges.end());

    int r = 0;

    for (int i = 1; i < (int)ranges.size(); i++)
    {
      if (ranges[r].second >= ranges[i].first)
      {
        ranges[r].second = max(ranges[r].second, ranges[i].second);
      }
      else
      {
        r++;
        ranges[r] = ranges[i];
      }
    }

    if (r > 0)
    {
      long long X = ((ranges[0].second + 1) * 4000000) + y;
      cout << X << "\n";
      return;
    }
  }
}
