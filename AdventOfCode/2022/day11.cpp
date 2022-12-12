#include "lib.h"

struct monkey
{
  vector<ll> items;
  string     operation;
  ll         divisibleBy;
  int        throwToTrue;
  int        throwToFalse;
  ll         inspect = 0;
};

bool IsiDivisibleBy(ll a, ll b)
{
  return (a % b == 0) ? true : false;
}

ll divRoundDown(ll aWorryLvl)
{
  return floor(aWorryLvl / 3);
}

ll GetMultiplied(string line, ll worrylvl)
{
  if (line.find('+') != string::npos)
  {
    vector<int> items;
    ExtractSignedInts(line, items);
    if (items.size() == 2)
      return ll(items[0]) + ll(items[1]);
    else if (items.size() == 1)
      return ll(items.front()) + worrylvl;
    else
      return worrylvl + worrylvl;
  }

  if (line.find('*') != string::npos)
  {
    vector<int> items;
    ExtractSignedInts(line, items);
    if (items.size() == 2)
      return ll(items.front()) * ll(items.back());
    else if (items.size() == 1)
      return ll(items.front()) * worrylvl;
    else
      return worrylvl * worrylvl;
  }

  return 0;
}

void day11()
{
  ifstream fin("data.txt");
  string   line;

  vector<monkey> monkeys;

  while (!fin.eof())
  {
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    monkey      currentonkey;
    vector<int> items;
    ExtractSignedInts(line, items);
    for (auto item : items)
      currentonkey.items.push_back(item);

    getline(fin, line);
    currentonkey.operation = line;

    getline(fin, line);
    items.clear();
    ExtractSignedInts(line, items);
    currentonkey.divisibleBy = items.front();

    getline(fin, line);
    items.clear();
    ExtractSignedInts(line, items);
    currentonkey.throwToTrue = items.front();

    getline(fin, line);
    items.clear();
    ExtractSignedInts(line, items);
    currentonkey.throwToFalse = items.front();

    monkeys.push_back(currentonkey);
  }

  // get cmmmc of each monkey divisible number
  ll cmmmc = 1;
  for (const auto & m : monkeys)
  {
    cmmmc = CMMMC(cmmmc, m.divisibleBy);
  }

  // rounds
  for (ll i = 0; i < 20; i++)
  {
    for (auto & m : monkeys)
    {
      for (auto item : m.items)
      {
        ll currentWorryLvl = GetMultiplied(m.operation, item);

        // p1
        // currentWorryLvl = divRoundDown(currentWorryLvl);

        // p2
        //  currentWorryLvl %= cmmmc;

        IsiDivisibleBy(currentWorryLvl, m.divisibleBy)
          ? monkeys[m.throwToTrue].items.push_back(currentWorryLvl)
          : monkeys[m.throwToFalse].items.push_back(currentWorryLvl);

        m.inspect++;
      }

      m.items.clear();
    }
  }

  vector<ll> inspections;
  for (auto m : monkeys)
  {
    inspections.push_back(m.inspect);
  }

  sort(inspections.begin(), inspections.end(), greater<>());

  cout << inspections[0] * inspections[1];
}
