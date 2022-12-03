#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

using ull = unsigned long long;

// Lowercase item types a through z have priorities 1 through 26.
// Uppercase item types A through Z have priorities 27 through 52.

int main()
{
  wifstream fin("data.txt");
  wstring   line;

  vector<wstring> data;
  vector<ull>     numbers;

  while (!fin.eof())
  {
    getline(fin, line);

    data.push_back(line);
  }

  for (auto line : data)
  {
    auto length = line.size();

    auto str1 = line.substr(0, length / 2);
    auto str2 = line.substr(length / 2, line.size());

    for (auto ch : str1)
    {
      if (str2.find(ch) != string::npos)
      {
        if (islower(ch))
          numbers.push_back(ch - 96);
        else
          numbers.push_back(ch - 38);
        break;
      }
    }
  }

  cout << "Sum: " << accumulate(numbers.begin(), numbers.end(), 0);

  vector<ull> numbers2;
  for (int i = 0; i < data.size();)
  {
    auto str1 = data[i++];
    auto str2 = data[i++];
    auto str3 = data[i++];

    for (auto ch : str1)
    {
      if ((str2.find(ch) != string::npos) && (str3.find(ch) != string::npos))
      {
        if (islower(ch))
          numbers2.push_back(ch - 96);
        else
          numbers2.push_back(ch - 38);
        break;
      }
    }
  }

  cout << "\nSum: " << accumulate(numbers2.begin(), numbers2.end(), 0);

  return 0;
}
