#include "../stdafx.h"

constexpr int ROCKVAL     = 1;
constexpr int PAPERVAL    = 2;
constexpr int SCISSORSVAL = 3;

constexpr int WINVAL  = 6;
constexpr int DRAWVAL = 3;
constexpr int LOSEVAL = 0;

constexpr wchar_t ROCK     = 'A';
constexpr wchar_t PAPER    = 'B';
constexpr wchar_t SCISSORS = 'C';

constexpr wchar_t ROCKENCODE     = 'X';  // second half lose
constexpr wchar_t PAPERENCODE    = 'Y';  // second half draw
constexpr wchar_t SCISSORSENCODE = 'Z';  // second half win

void day2()
{
  wifstream fin("data.txt");
  wstring   line;

  vector<ull> dataFirstHalf;
  vector<ull> dataSecondHalf;

  while (!fin.eof())
  {
    getline(fin, line);

    if (line[0] == ROCK)
    {
      if (line[2] == ROCKENCODE)
      {
        dataFirstHalf.push_back(ROCKVAL + DRAWVAL);
        // need to lose
        dataSecondHalf.push_back(SCISSORSVAL + LOSEVAL);
      }
      if (line[2] == PAPERENCODE)
      {
        dataFirstHalf.push_back(PAPERVAL + WINVAL);
        // draw
        dataSecondHalf.push_back(ROCKVAL + DRAWVAL);
      }
      if (line[2] == SCISSORSENCODE)
      {
        dataFirstHalf.push_back(SCISSORSVAL + LOSEVAL);
        // win
        dataSecondHalf.push_back(PAPERVAL + WINVAL);
      }
    }
    else if (line[0] == PAPER)
    {
      if (line[2] == ROCKENCODE)
      {
        dataFirstHalf.push_back(ROCKVAL + LOSEVAL);
        // need to lose
        dataSecondHalf.push_back(ROCKVAL + LOSEVAL);
      }
      if (line[2] == PAPERENCODE)
      {
        dataFirstHalf.push_back(PAPERVAL + DRAWVAL);
        // draw
        dataSecondHalf.push_back(PAPERVAL + DRAWVAL);
      }
      if (line[2] == SCISSORSENCODE)
      {
        dataFirstHalf.push_back(SCISSORSVAL + WINVAL);
        // win
        dataSecondHalf.push_back(SCISSORSVAL + WINVAL);
      }
    }
    else if (line[0] == SCISSORS)
    {
      if (line[2] == ROCKENCODE)
      {
        dataFirstHalf.push_back(ROCKVAL + WINVAL);
        // need to lose
        dataSecondHalf.push_back(PAPERVAL + LOSEVAL);
      }
      if (line[2] == PAPERENCODE)
      {
        dataFirstHalf.push_back(PAPERVAL + LOSEVAL);
        // draw
        dataSecondHalf.push_back(SCISSORSVAL + DRAWVAL);
      }
      if (line[2] == SCISSORSENCODE)
      {
        dataFirstHalf.push_back(SCISSORSVAL + DRAWVAL);
        // win
        dataSecondHalf.push_back(ROCKVAL + WINVAL);
      }
    }
  }

  cout << "First half: " << accumulate(dataFirstHalf.begin(), dataFirstHalf.end(), 0);
  cout << "\nSecond half: " << accumulate(dataSecondHalf.begin(), dataSecondHalf.end(), 0);
}
