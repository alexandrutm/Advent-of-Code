#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <queue>
#include <array>
#include <variant>
#include <string_view>
#include <regex>
#include <sstream>

using namespace std;

struct point {
	long long x, y;
};

struct senzor {
	point Pos;

	set<pair<long long, long long>> detectedPositions;
};

long long distanceManh(point a, point  b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void ExtractSignedlong (string s, vector<point>& aNumbers)
{
	std::regex rx("-?\\d+");

	std::smatch match;

	auto words_begin = sregex_iterator(s.begin(), s.end(), rx);
	auto words_end = sregex_iterator();

	for (auto i = words_begin; i != words_end; ++i)
	{
		smatch match = *i;
		long long x = stoi(match.str());

		++i;
		match = *i;
		long long y = stoi(match.str());

		aNumbers.push_back(point(x, y));
	}
}

void main() {

	ifstream fin("data.txt");

	string inputLine;

	vector<pair<senzor, point>> senzorBeacons;

	long long highestY = 0;

	while (!fin.eof())
	{
		getline(fin, inputLine);
		vector<point> coord;

		ExtractSignedlong(inputLine, coord);

		senzor sen;
		sen.Pos = coord[0];

		senzorBeacons.push_back(make_pair(sen, coord[1]));
	}


	long long yMAX = 2000000;

	for (auto& senzorBeacon : senzorBeacons)
	{
		//get dist to c
		auto distManh = distanceManh(senzorBeacon.first.Pos, senzorBeacon.second);

		//mark all positions from senzor + dist as detected
		long long senzorPosX = senzorBeacon.first.Pos.x;
		long long senzorPosY = senzorBeacon.first.Pos.y;

		if (senzorPosY < yMAX)
		{
			for (long long currentY = senzorPosY; currentY <= senzorPosY + distManh; currentY++)
			{
				if (currentY == yMAX)
				{
					long long distX = (senzorPosY+distManh)-currentY;

					for (long long x = senzorPosX- distX; x <= senzorPosX + distX; x++)
					{
						senzorBeacon.first.detectedPositions.insert(make_pair(x, currentY));
					}

				}
			}
		}
		else if (senzorPosY > yMAX)
		{
			for (long long currentY = senzorPosY; currentY >= senzorPosY - distManh; currentY--)
			{
				if (currentY == yMAX)
				{
					long long distX = (currentY + distManh) - senzorPosY;

					for (long long x = senzorPosX - distX; x <= senzorPosX + distX; x++)
					{
						senzorBeacon.first.detectedPositions.insert(make_pair(x, currentY));
					}

				}
			}
		}
		else
		{
			for (long long x = senzorPosX - distManh; x <= senzorPosX + distManh; x++)
			{
				senzorBeacon.first.detectedPositions.insert(make_pair(x, senzorPosY));
			}
		}
	}

	set<pair<long long, long long>> positions;

	for (auto senzorBeacon : senzorBeacons)
	{
		for (auto pos : senzorBeacon.first.detectedPositions)
		{		positions.insert(make_pair(pos.first,pos.second));
		}
	}

	set<long long>nrBeacons;

	for (auto senzorBeacon : senzorBeacons)
	{
		auto found=positions.find(make_pair(senzorBeacon.second.x, senzorBeacon.second.y));

		if (found != positions.end())
			nrBeacons.insert(senzorBeacon.second.x);
	}

	cout << positions.size()- nrBeacons.size();

}