#include "../lib.h"

void day5()
{
  ifstream fin("data.txt");

  string line;

  vector<string> data;

  vector<string> numbers{ { "RNPG" },  { "TJBLCSVH" }, { "TDBMNL" },
                          { "RVPSB" }, { "GCQSWMVH" }, { "WQSCDBJ" },
                          { "FQL" },   { "WMHTDLFV" }, { "LPBVMJF" } };

  vector<stack<char>> data2;

  for (auto line : numbers)
  {
    stack<char> a;

    for (auto i : line)
      a.push(i);

    data2.push_back(a);

    a = stack<char>();
  }

  while (!fin.eof())
  {
    getline(fin, line);

    vector<int> instructions;

    GetAllIntsFromStringLine(line, instructions);

    stack<int> intermed;

    for (int i = 0; i < instructions[0]; i++)
    {
      intermed.push(data2[instructions[1] - 1].top());
      data2[instructions[1] - 1].pop();
    }

    for (int i = 0; i < instructions[0]; i++)
    {
      data2[instructions[2] - 1].push(intermed.top());
      intermed.pop();
    }

    // for (int i = 0; i < instructions[0]; i++)
    //{
    //   data2[instructions[2] - 1].push(data2[instructions[1] - 1].top());
    //   data2[instructions[1] - 1].pop();
    // }
  }

  for (auto st : data2)
  {
    cout << st.top();
  }
}

int main()
{
  day5();
  return 0;
}
