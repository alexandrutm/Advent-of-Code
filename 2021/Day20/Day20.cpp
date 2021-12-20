#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int GetValueForNextPixel(const string & matrix)
{
  string value;
  for (auto i : matrix)
  {
    if (i == '.')
      value += '0';
    else if (i == '#')
      value += '1';
  }

  return std::stoi(value, nullptr, 2);
}

void AddMargines(vector<string> & aImage)
{
  string s2;
  for (int i = 0; i < 110; i++)
    s2.push_back('.');

  for (int i = 0; i < aImage.size(); i++)
  {
    aImage[i].insert(0, s2);
    aImage[i].append(s2);
  }

  string a;
  for (int i = 0; i < aImage[0].size(); i++)
    a.push_back('.');

  for (int i = 0; i < 60; i++)
  {
    aImage.insert(aImage.begin(), a);
    aImage.push_back(a);
  }
}

void ReadData(string & aEnhancementAlgorithm, vector<string> & aImage)
{
  ifstream fin("input.txt");
  string   imgLine;

  getline(fin, aEnhancementAlgorithm);
  getline(fin, imgLine);

  while (getline(fin, imgLine))
  {
    vector<int> valueLine;

    aImage.push_back(imgLine);
  }
  AddMargines(aImage);
}

void GetNewImage(string aEnhancementAlgorithm, vector<string> & aImage)
{
  vector<string> newImg;
  newImg = aImage;

  for (int i = 1; i < aImage.size() - 1; i++)
  {
    for (int j = 1; j < aImage[i].size() - 1; j++)
    {
      string matrixLine;

      matrixLine += aImage[i - 1][j - 1];
      matrixLine += aImage[i - 1][j];
      matrixLine += aImage[i - 1][j + 1];
      matrixLine += aImage[i][j - 1];
      matrixLine += aImage[i][j];
      matrixLine += aImage[i][j + 1];
      matrixLine += aImage[i + 1][j - 1];
      matrixLine += aImage[i + 1][j];
      matrixLine += aImage[i + 1][j + 1];

      // get pos from alg
      int pos = GetValueForNextPixel(matrixLine);

      if (aEnhancementAlgorithm[pos] == '#')
      {
        newImg[i][j] = '#';
      }
      else if (aEnhancementAlgorithm[pos] == '.')
      {
        newImg[i][j] = '.';
      }
    }
  }

  aImage = newImg;
}

void PrintToFile(const vector<string> & image)
{
  ofstream fout("output.txt");
  // print a lot of # in margins - so start print and count with i from 5 and j from 50 to size-40

  for (int i = 5; i < image.size(); i++)
  {
    for (int j = 50; j < image[i].size() - 40; j++)
    {
      fout << image[i][j];
    }
    fout << "\n";
  }
}

int CountLitPixels(const vector<string> & image)
{
  int count = 0;
  for (int i = 5; i < image.size(); i++)
  {
    for (int j = 50; j < image[i].size() - 40; j++)
    {
      image[i][j] == '#' ? count++ : 0;
    }
  }

  return count;
}

int main()
{
  ifstream fin("input.txt");
  if (!fin.is_open())
  {
    cout << "File not found";
  }

  string         enhancementAlgorithm;
  vector<string> image;
  ReadData(enhancementAlgorithm, image);

  for (int i = 0; i < 50; i++)
    GetNewImage(enhancementAlgorithm, image);

  PrintToFile(image);
  cout << CountLitPixels(image);

  return 0;
}
