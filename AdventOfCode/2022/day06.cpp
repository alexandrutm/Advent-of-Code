#include "../lib.h"

void day06()
{
  ifstream fin("data.txt");

  string line;

  while (!fin.eof())
  {
    getline(fin, line);

    for (int i = 0; i < line.size() - 4; i++)
    {
      if (UniqueCharacters(line.substr(i, 4)))
      {
        cout << "Part 1: " << i + 4;
        break;
      }
    }

    for (int i = 0; i < line.size() - 14; i++)
    {
      if (UniqueCharacters(line.substr(i, 14)))
      {
        cout << "\nPart 2: " << i + 14;
        break;
      }
    }
  }
}
