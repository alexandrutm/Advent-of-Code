#include "../lib.h"

struct point
{
  int x = 0, y = 0;

  bool operator==(const point & p) const { return x == p.x && y == p.y; }
  bool operator<(const point & p) const { return x < p.x && y < p.y; }
};

int ManhDist(point aHead, point aTail)
{
  return (abs(aHead.x - aTail.x) + abs(aHead.y - aTail.y));
}

bool IsNeighbour(point aHead, point aTail)
{
  for (int i = -1; i < 2; i++)
  {
    for (int j = -1; j < 2; j++)
    {
      if (aTail.x + i == aHead.x && aTail.y + j == aHead.y)
      {
        return true;
      }
    }
  }

  return false;
}

void move_tail(vector<point> & aRope, const char aDirection)
{
  if (ManhDist(aRope.front(), aRope.back()) == 2 && IsNeighbour(aRope.front(), aRope.back()))
    return;

  if (ManhDist(aRope.front(), aRope.back()) >= 2)
  {
    if (aDirection == 'U')
    {
      aRope.back().x = aRope.front().x + 1;
      aRope.back().y = aRope.front().y;
    }
    else if (aDirection == 'R')
    {
      aRope.back().y = aRope.front().y - 1;
      aRope.back().x = aRope.front().x;
    }
    else if (aDirection == 'D')
    {
      aRope.back().x = aRope.front().x - 1;
      aRope.back().y = aRope.front().y;
    }
    else if (aDirection == 'L')
    {
      aRope.back().y = aRope.front().y + 1;
      aRope.back().x = aRope.front().x;
    }
  }
}

void move_rope(vector<point> & aRope, const char aDirection)
{
  if (aDirection == 'U')
  {
    aRope.front().x -= 1;
    move_tail(aRope, aDirection);
  }
  else if (aDirection == 'R')
  {
    aRope.front().y += 1;
    move_tail(aRope, aDirection);
  }
  else if (aDirection == 'D')
  {
    aRope.front().x += 1;
    move_tail(aRope, aDirection);
  }
  else if (aDirection == 'L')
  {
    aRope.front().y -= 1;
    move_tail(aRope, aDirection);
  }
}

void day09()
{
  ifstream fin("data.txt");
  string   line;

  set<pair<int, int>> visited;

  vector<point> rope;

  point start, tail, head;

  rope.push_back(head);
  rope.push_back(tail);

  char direction;
  int  steps;

  while (fin >> direction >> steps)
  {
    for (int i = 0; i < steps; ++i)
    {
      move_rope(rope, direction);
      visited.insert(make_pair(rope.back().x, rope.back().y));
    }
  }

  cout << visited.size();
}

void main()
{
  day09();
}
