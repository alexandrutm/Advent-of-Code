#include "../lib.h"

struct point
{
  int x, y;
};

vector<point> GetPiece(int aPiecePos, int aY)
{
  if (aPiecePos == 0)
  {
    return { { 2, aY }, { 3, aY }, { 4, aY }, { 5, aY } };
  }
  else if (aPiecePos == 1)
  {
    return { { 3, aY + 2 }, { 2, aY + 1 }, { 3, aY + 1 }, { 4, aY + 1 }, { 3, aY } };
  }
  else if (aPiecePos == 2)
  {
    return { { 2, aY }, { 3, aY }, { 4, aY }, { 4, aY + 1 }, { 4, aY + 2 } };
  }
  else if (aPiecePos == 3)
  {
    return { { 2, aY }, { 2, aY + 1 }, { 2, aY + 2 }, { 2, aY + 3 } };
  }
  else if (aPiecePos == 4)
  {
    return { { 2, aY + 1 }, { 2, aY }, { 3, aY + 1 }, { 3, aY } };
  }
}

void MoveLeft(vector<point> & aPiece)
{
  for (auto & point : aPiece)
    if (point.x == 0)
      return;

  for (auto & point : aPiece)
  {
    point.x -= 1;
  }
}

void MoveRight(vector<point> & aPiece)
{
  for (auto & point : aPiece)
    if (point.x == 6)
      return;

  for (auto & point : aPiece)
  {
    point.x += 1;
  }
}

void MoveDown(vector<point> & aPiece)
{
  for (auto & point : aPiece)
  {
    point.y -= 1;
  }
}

void MoveUp(vector<point> & aPiece)
{
  for (auto & point : aPiece)
  {
    point.y += 1;
  }
}

bool CheckCave(vector<vector<char>> & aCave, vector<point> aPiece)
{
  // if one of piece point is already a rock return to old state
  for (auto pnt : aPiece)
  {
    if (aCave[pnt.y][pnt.x] == '#')
      return true;
  }

  return false;
}

void UpdateCave(vector<vector<char>> & aCave, vector<point> aPiece)
{
  for (auto pnt : aPiece)
  {
    aCave[pnt.y][pnt.x] = '#';
  }
}

int GetCaveTop(vector<vector<char>> & aCave)
{
  int max = 0, i = 0;

  for (auto line : aCave)
  {
    for (auto col : line)
      if (col == '#')
      {
        max = i;
        break;
      }

    if (max != i)
      return max;

    i++;
  }

  return max;
}

void main()
{
  ifstream fin("data.txt");
  string   directions;
  getline(fin, directions);

  int sky            = 0;
  int pieceIndex     = 0;
  int directionIndex = 0;

  vector<vector<char>> cave(100000, vector<char>(7, '.'));
  fill(cave[0].begin(), cave[0].end(), '#');

  int droppedPieces = 0;

  long long maxPiece = 1000000000000;

  while (1)
  {
    auto currentPiece = GetPiece(pieceIndex % 5, sky + 4);
    while (1)
    {
      if (directions[directionIndex] == '<')
      {
        MoveLeft(currentPiece);
        if (CheckCave(cave, currentPiece))
          MoveRight(currentPiece);
      }
      else
      {
        MoveRight(currentPiece);
        if (CheckCave(cave, currentPiece))
          MoveLeft(currentPiece);
      }

      // circular directions
      directionIndex = (directionIndex + 1) % directions.size();

      MoveDown(currentPiece);
      if (CheckCave(cave, currentPiece))
      {
        MoveUp(currentPiece);
        UpdateCave(cave, currentPiece);

        sky = GetCaveTop(cave);
        pieceIndex++;
        break;
      }
    }

    droppedPieces++;

    if (droppedPieces == 2022)
    {
      cout << sky << "\n";
      return;
    }
  }
}
