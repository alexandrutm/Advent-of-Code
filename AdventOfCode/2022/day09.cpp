#include "../lib.h"

struct point
{
  int x = 0, y = 0;

  bool operator==(const point & p) const { return x == p.x && y == p.y; }
  bool operator<(const point & p) const { return x < p.x && y < p.y; }
};

void move_tail(point & aHead, point & aTail)
{
  int x = aHead.x - aTail.x;
  int y = aHead.y - aTail.y;

  if (abs(x) > 1 || abs(y) > 1)
  {
    if (x == 0)
      aTail.y += y / 2;
    else if (y == 0)
      aTail.x += x / 2;
    else
    {
      aTail.x += (x > 0) ? 1 : -1;
      aTail.y += (y > 0) ? 1 : -1;
    }
  }
}

void day09()
{
  ifstream fin("data.txt");
  string   line;

  set<pair<int, int>> visited;

  vector<point> rope;

  point head;

  // p1
  // rope.push_back(head);
  // rope.push_back(head);

  // p2
  int i = 0;
  while (i < 10)
  {
    rope.push_back(head);
    i++;
  }

  char direction;
  int  steps;

  while (fin >> direction >> steps)
  {
    for (int i = 0; i < steps; ++i)
    {
      int dx = direction == 'R' ? 1 : (direction == 'L' ? -1 : 0);
      int dy = direction == 'U' ? 1 : (direction == 'D' ? -1 : 0);

      rope.front().x += dx;
      rope.front().y += dy;

      // p1
      // move_tail(rope.front(), rope.back());

      for (int i = 0; i < rope.size() - 1; i++)
        move_tail(rope[i], rope[i + 1]);

      visited.insert(make_pair(rope.back().x, rope.back().y));
    }
  }

  cout << visited.size();
}
