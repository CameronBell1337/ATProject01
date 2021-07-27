#include "Map.h"
#include "Grnd.h"
#include "Objects.h"
#include "Wave.h"

#include <sstream>
#include <string>
#include <algorithm>

Map::Map(Graphics& graphics)
{
	
	//Switch out to reading from a text file
	int gridDims[] =
	{
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,
		3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
		3,2,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,2,3,
		1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,
		3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	};

	grnd.reserve(mapW);
	for (auto x = 0; x < mapW; x++)
	{
		grnd.emplace_back();
		grnd.back().reserve(mapH);
		for (auto y = 0; y < mapH; y++)
		{
			if (gridDims[x + y * mapW] == 0)
			{
				mainColours = colours0;
			}
			else if (gridDims[x + y *mapW] == 1)
			{
				mainColours = colours1;
			}
			else if (gridDims[x + y * mapW] == 2)
			{
				mainColours = colours2;
			}
			else if (gridDims[x + y * mapW] == 3)
			{
				mainColours = colours3;
			}

			grnd.back().emplace_back(graphics, mainColours);;
			Vector3 coords;

			coords.x = x;
			coords.y = y;
			grnd.back().back().SetPos(coords);

		}
	}

	wp.reserve(14);
	wp.emplace_back(wayPoint13, nullptr);
	wp.emplace_back(wayPoint12, &wp.back());
	wp.emplace_back(wayPoint11, &wp.back());
	wp.emplace_back(wayPoint10, &wp.back());
	wp.emplace_back(wayPoint9, &wp.back());
	wp.emplace_back(wayPoint8, &wp.back());
	wp.emplace_back(wayPoint7, &wp.back());
	wp.emplace_back(wayPoint6, &wp.back());
	wp.emplace_back(wayPoint5, &wp.back());
	wp.emplace_back(wayPoint4, &wp.back());
	wp.emplace_back(wayPoint3, &wp.back());
	wp.emplace_back(wayPoint2, &wp.back());
	wp.emplace_back(wayPoint1, &wp.back());
	wp.emplace_back(wayPoint0, &wp.back());


	Wave* wave = new Wave(&wp.back());
	Objects::CreateObj(wave);
}

Waypoint* Map::GetNextWP()
{
	return &wp.back();
}

Grnd* Map::GetGrnd(Vector3 pos)
{
	
	return GetGrndCoord(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

Grnd* Map::GetGrndCoord(int x, int y)
{
	if (x < 0 || y < 0 || x >= mapW || y >= mapH)
	{
		return nullptr;
	}

	return &grnd[x][y];
}

//TOFIX
void Map::SetColour(DirectX::XMFLOAT3 colour)
{
	mainColours = colour;
}

void Map::DrawObj(Graphics& graphics)
{
	for (auto& c : grnd)
	{
		for (auto& _map : c)
		{
			_map.DrawObj(graphics);
		}
	}
}

void Map::SetPos(Vector3 _pos) noexcept
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->pos.z = pos.z;
}

