#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void ParseStringToVectorInt(const string & str, vector<int> & result)
{
  typedef regex_iterator<std::string::const_iterator> re_iterator;
  typedef re_iterator::value_type                     re_iterated;

  regex re("(\\d+)");

  re_iterator rit(str.begin(), str.end(), re);
  re_iterator rend;

  transform(rit, rend, std::back_inserter(result),
            [](const re_iterated & it)
            {
              return std::stoi(it[1]);
            });
}

bool IsTheMagicNumber(const vector<vector<int>> & m)
{
  for (int i = 0; i < m.size(); i++)
  {
    bool foundLine = false;
    for (int j = 0; j < m[i].size(); j++)
    {
      if (m[i][j] != 1)
      {
        foundLine = false;
        break;
      }
      else
      {
        foundLine = true;
      }
    }

    if (foundLine == true)
      return true;

    bool foundCol = false;
    for (int j = 0; j < m.size(); j++)
    {
      if (m[j][i] != 1)
      {
        foundCol = false;
        break;
      }
      else
      {
        foundCol = true;
      }
    }

    if (foundCol == true)
      return true;
  }
  return false;
}

void PrintResultPart1(int                         magicNumber,
                      const vector<vector<int>> & matrix,
                      const vector<int> &         numbersList)
{
  int sum = 0;

  for (int j = 0; j < matrix.size(); j++)
  {
    for (int k = 0; k < matrix[j].size(); k++)
    {
      bool notFound = false;
      for (int i = 0; i < numbersList.size(); i++)
      {
        if (matrix[j][k] == numbersList[i])
        {
          notFound = false;
          break;
        }
        else
          notFound = true;
      }

      if (notFound)
      {
        sum += matrix[j][k];
      }
    }
  }

  cout << "Part 1: " << sum * magicNumber;
}

bool isBoardWinnable(const vector<vector<int>> & matrix, const vector<int> & numbersList)
{
  vector<vector<int>> m;
  m.resize(matrix.size(), vector<int>(matrix[0].size()));
  fill(m.begin(), m.end(), std::vector<int>(matrix.size(), 0));

  for (int i = 0; i < numbersList.size(); i++)
  {
    for (int j = 0; j < matrix.size(); j++)
    {
      for (int k = 0; k < matrix[j].size(); k++)
      {
        if (numbersList[i] == matrix[j][k])
        {
          m[j][k] = 1;
          if (IsTheMagicNumber(m))
          {
            PrintResultPart1(matrix[j][k], matrix, numbersList);
            return true;
          }
        }
      }
    }
  }
  return false;
}

void BothParts()
{
  vector<int>                 numbersList;
  vector<vector<vector<int>>> theMatrixs;

  ifstream fin("input.txt");
  string   str;

  fin >> str;
  ParseStringToVectorInt(str, numbersList);

  while (!fin.eof())
  {
    vector<vector<int>> matrix;
    string              currentLine;

    vector<int> matrixLine;
    while (getline(fin, currentLine))
    {
      if (currentLine == "")
        break;

      ParseStringToVectorInt(currentLine, matrixLine);
      matrix.push_back(matrixLine);
      matrixLine.clear();
    }

    if (matrix.size() > 0)
    {
      theMatrixs.push_back(matrix);
    }
  }

  // for each matrix check if by adding one number it s the winning one

  vector<int> test;
  test.resize(numbersList.size());
  fill(test.begin(), test.end(), 0);

  for (int i = 0; i < numbersList.size(); i++)
  {
    vector<int>::const_iterator first = numbersList.begin();
    vector<int>::const_iterator last  = numbersList.begin() + i;
    vector<int>                 newVec(first, last);
    int                         j = 0;

    for (auto matrix : theMatrixs)
    {
      if (test[j] != 1 && isBoardWinnable(matrix, newVec))
      {
        test[j] = 1;
      }
      j++;
    }
  }
}

int main()
{
  BothParts();
}
