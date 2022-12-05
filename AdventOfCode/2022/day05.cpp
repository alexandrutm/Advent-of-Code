#include "../lib.h"

void day5()
{
  ifstream fin("data.txt");

  string line;

  vector<string> initialCratesState{ { "RNPG" },  { "TJBLCSVH" }, { "TDBMNL" },
                                     { "RVPSB" }, { "GCQSWMVH" }, { "WQSCDBJ" },
                                     { "FQL" },   { "WMHTDLFV" }, { "LPBVMJF" } };

  vector<stack<char>> cratesStacksP1;
  vector<stack<char>> cratesStacksP2;

  for (auto line : initialCratesState)
  {
    stack<char> stk;

    for (auto i : line)
      stk.push(i);

    cratesStacksP1.push_back(stk);
    cratesStacksP2.push_back(stk);
  }

  while (!fin.eof())
  {
    getline(fin, line);

    vector<int> instructions;

    ExtractSignedInts(line, instructions);

    // p1
    for (int i = 0; i < instructions[0]; i++)
    {
      cratesStacksP1[instructions[2] - 1].push(cratesStacksP1[instructions[1] - 1].top());
      cratesStacksP1[instructions[1] - 1].pop();
    }

    // p2
    stack<int> intermediarStk;

    for (int i = 0; i < instructions[0]; i++)
    {
      intermediarStk.push(cratesStacksP2[instructions[1] - 1].top());
      cratesStacksP2[instructions[1] - 1].pop();
    }

    for (int i = 0; i < instructions[0]; i++)
    {
      cratesStacksP2[instructions[2] - 1].push(intermediarStk.top());
      intermediarStk.pop();
    }
  }

  cout << "Part 1:  ";
  for (auto st : cratesStacksP1)
  {
    cout << st.top();
  }

  cout << "\nPart 2:  ";
  for (auto st : cratesStacksP2)
  {
    cout << st.top();
  }
}
