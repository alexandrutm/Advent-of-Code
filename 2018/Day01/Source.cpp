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

int main()
{
  wifstream   fin("data.txt");
  vector<ull> numbers;

  while (!fin.eof())
  {
    ull     value;
    wstring line;

    getline(fin, line);

    numbers.push_back(stoull(line));
  }

  // first star
  cout << "Sum: " << accumulate(numbers.begin(), numbers.end(), 0);

  // second star

  vector<ull> freq;
  ull         currentFreq = 0;
  int         i           = 0;

  while (find(freq.begin(), freq.end(), currentFreq) == freq.end())
  {
    freq.push_back(currentFreq);

    currentFreq += numbers[i++];

    if (i == numbers.size())
      i = 0;
  }

  cout << "\n Duplicate frequency: " << currentFreq;
  return 0;
}
