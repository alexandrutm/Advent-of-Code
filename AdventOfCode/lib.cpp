#include "stdafx.h"
#include "lib.h"

ll CMMDC(ll aFirst, ll aSecond)
{
  if (aFirst == 0)
    return aSecond;

  return CMMDC(aSecond % aFirst, aFirst);
}

ll CMMMC(ll aFirst, ll aSecond)
{
  return (aFirst * aSecond) / CMMDC(aFirst, aSecond);
}

void ExtractSignedInts(const string & aStr, vector<int> & aNumbers)
{
  stringstream ss;
  ss << aStr;
  string temp;

  int found;
  while (!ss.eof())
  {
    ss >> temp;
    if (stringstream(temp) >> found)
      aNumbers.push_back(found);

    /* To save from space at the end of string */
    temp = "";
  }
}

bool UniqueCharacters(const string & str)
{
  for (int i = 0; i < str.length() - 1; i++)
  {
    for (int j = i + 1; j < str.length(); j++)
    {
      if (str[i] == str[j])
      {
        return false;
      }
    }
  }

  return true;
}
