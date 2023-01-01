#include "../lib.h"

using namespace std;
typedef long long ll;

ll modulo(ll a, ll b)
{
  return (a % b + b) % b;
}

struct numbers
{
  int64_t index;
  int64_t val;
};

bool operator==(const numbers & a, const numbers & b)
{
  return tuple(a.index, a.val) == tuple(b.index, b.val);
}

void main()
{
  // read
  ifstream        fin("data.txt");
  vector<numbers> initialState;

  ll value;

  // p2
  const ll decryptionKey = 811589153;
  int      rounds        = 10;

  int i = 0;
  while (!fin.eof())
  {
    fin >> value;
    initialState.push_back({ i++, value * decryptionKey });
  }

  auto alterState = initialState;
  ll   vecSize    = initialState.size() - 1;

  while (rounds)
  {
    for (auto val : initialState)
    {
      auto from    = find(begin(alterState), end(alterState), val);
      auto nextPos = modulo(distance(alterState.begin(), from) + val.val, vecSize);

      alterState.erase(from);
      alterState.insert(alterState.begin() + nextPos, val);
    }
    rounds--;
  }

  auto zeroPos = distance(alterState.begin(), find_if(alterState.begin(), alterState.end(),
                                                      [](auto & num)
                                                      {
                                                        return num.val == 0;
                                                      }));

  auto posFirstVal  = (1000 + zeroPos) % alterState.size();
  auto posSecondVal = (2000 + zeroPos) % alterState.size();
  auto posThirdVal  = (3000 + zeroPos) % alterState.size();

  cout << "Sum: "
       << alterState[posFirstVal].val + alterState[posSecondVal].val + alterState[posThirdVal].val;
}
