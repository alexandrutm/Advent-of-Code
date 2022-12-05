#include "stdafx.h"
#include "lib.h"

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
