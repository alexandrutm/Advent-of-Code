#include "../lib.h"

void ComputeString(string & output, int spritepos, int currentCol)
{
  if (spritepos - 1 == currentCol || spritepos == currentCol || spritepos + 1 == currentCol)
    output.push_back('#');
  else
    output.push_back('.');
}

void day10()
{
  ifstream fin("data.txt");
  string   line;

  vector<pair<string, int>> data;

  int lastValue;

  while (!fin.eof())
  {
    getline(fin, line);

    int value;
    if (!line.substr(4).empty())
      value = stoi(line.substr(4));
    else
      value = 0;

    auto cmd = line.substr(0, 4);

    data.push_back(make_pair(cmd, value));
  }

  int iter   = 20;
  int cicles = 0;

  vector<int> sums;

  int    registerX  = 1;
  int    spritepos  = 1;
  int    currentCol = 0;
  string output;
  int    oldSum = 1;

  for (int i = 0; i < data.size(); i++)
  {
    string cmd;
    int    value;
    cmd   = data[i].first;
    value = data[i].second;

    if (cmd == "addx")
    {
      cicles += 1;
      // starts from pos 0 ********************************************
      currentCol = (cicles % 40) - 1;
      ComputeString(output, spritepos, currentCol);

      cicles += 1;
      currentCol = (cicles % 40) - 1;
      ComputeString(output, spritepos, currentCol);

      registerX += value;

      // new val
      spritepos = registerX;
    }

    if (cmd == "noop")
    {
      cicles += 1;
      currentCol = (cicles % 40) - 1;
      ComputeString(output, spritepos, currentCol);
    }

    if (cicles == iter)
    {
      sums.push_back(cicles * oldSum);
      iter += 40;
    }
    else if (cicles > iter)
    {
      sums.push_back((cicles - 1) * oldSum);

      iter += 40;
    }

    oldSum = registerX;
  }

  cout << accumulate(sums.begin(), sums.end(), 0);

  cout << "\n";

  int startPrint = 0;
  int sizePrint  = 40;

  while (startPrint < output.size())
  {
    cout << output.substr(startPrint, sizePrint) << "\n";
    startPrint += sizePrint;
  }
}
