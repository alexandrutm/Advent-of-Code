#include "../includes.h"

/*
    [H]         [H]         [V]
    [V]         [V] [J]     [F] [F]
    [S] [L]     [M] [B]     [L] [J]
    [C] [N] [B] [W] [D]     [D] [M]
[G] [L] [M] [S] [S] [C]     [T] [V]
[P] [B] [B] [P] [Q] [S] [L] [H] [B]
[N] [J] [D] [V] [C] [Q] [Q] [M] [P]
[R] [T] [T] [R] [G] [W] [F] [W] [L]
 1   2   3   4   5   6   7   8   9
 */

void day5()
{
  wifstream fin("data.txt");

  wstring line;

  vector<wstring> data;

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

    wstringstream ss;

    /* Storing the whole string into string stream */
    ss << line;

    /* Running loop till the end of the stream */
    wstring temp;
    int     found;
    while (!ss.eof())
    {
      /* extracting word by word from stream */
      ss >> temp;

      /* Checking the given word is integer or not */
      if (wstringstream(temp) >> found)
        instructions.push_back(found);

      /* To save from space at the end of string */
      temp = L"";
    }

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
