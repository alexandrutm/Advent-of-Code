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

vector<vector<char>> GetLastState(vector<vector<char>> & aCave)
{
  vector<vector<char>> cave;

  int height = GetCaveTop(aCave);

  if (height < 40)
    return { {} };

  // get last 40 rows from cave
  int rIndex = 0;
  for (auto row : aCave)
  {
    if (rIndex < height - 40)
    {
      rIndex++;
      continue;
    }

    cave.push_back(row);

    if (rIndex == height - 1)
      return cave;

    rIndex++;
  }

  return { {} };
}

struct caveView
{
  int instructionIndex, pieceIndex, currentTop, droppedPieces;

  vector<vector<char>> view;

  bool operator==(const caveView & r)
  {
    if (instructionIndex != r.instructionIndex || pieceIndex != r.pieceIndex)
      return false;

    for (int i = 0; i < view.size(); i++)
    {
      for (int j = 0; j < view[i].size(); j++)
      {
        if (view[i][j] != r.view[i][j])
          return false;
      }
    }

    return true;
  }
};

void day17()
{
  ifstream fin("data.txt");
  string   instructions;
  getline(fin, instructions);

  int top              = 0;
  int pieceIndex       = 0;
  int instructionIndex = 0;

  vector<vector<char>> cave(100000, vector<char>(7, '.'));
  fill(cave[0].begin(), cave[0].end(), '#');

  int droppedPieces = 0;

  long long maxPiece = 1000000000000;

  vector<caveView> states;

  while (droppedPieces < maxPiece)
  {
    auto currentPiece = GetPiece(pieceIndex % 5, top + 4);
    while (1)
    {
      if (instructions[instructionIndex] == '<')
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
      instructionIndex = (instructionIndex + 1) % instructions.size();

      MoveDown(currentPiece);
      if (CheckCave(cave, currentPiece))
      {
        MoveUp(currentPiece);
        UpdateCave(cave, currentPiece);

        top = GetCaveTop(cave);
        pieceIndex++;

        if (top > 40)
        {
          // check after each piece if we have a repetition
          // save current piece index, curent instruction, current top 40 rows
          caveView caveview;
          caveview.currentTop       = top;
          caveview.droppedPieces    = droppedPieces;
          caveview.instructionIndex = instructionIndex;
          caveview.pieceIndex       = pieceIndex % 5;
          caveview.view             = GetLastState(cave);

          auto pos = find(states.begin(), states.end(), caveview);
          if (pos != states.end() && droppedPieces > 2022)
          {
            // we have a repetition

            auto oldDroppedPiece = pos->droppedPieces;
            auto oldTop          = pos->currentTop;

            auto distTop          = top - oldTop;
            auto distDroppedPiece = droppedPieces - oldDroppedPiece;

            auto iterations = (maxPiece - droppedPieces) / distDroppedPiece;
            auto added      = iterations * distTop;

            auto ddroppedPieces = droppedPieces + (iterations * distDroppedPiece);

            if (ddroppedPieces >= maxPiece)
              return;

            cout << top + added << "\n";
          }
          else
            states.push_back(caveview);
        }

        break;
      }
    }

    droppedPieces++;

    if (droppedPieces == 2022)
    {
      cout << top << "\n";
    }
  }
}
