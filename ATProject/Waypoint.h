#pragma once
#include "Vector3.h"

class Waypoint
{
public:
	Waypoint(Vector3 pos, Waypoint* newWP = nullptr);
	Vector3 GetPos();
	Waypoint* GetNextWP();
private:
	Vector3 pos;
	Waypoint* nextWP = nullptr;
};