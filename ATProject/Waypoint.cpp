#include "Waypoint.h"

//Crude method of creating waypoints
Waypoint::Waypoint(Vector3 pos, Waypoint* WP) : pos(pos), nextWP(WP)
{}

Waypoint* Waypoint::GetNextWP()
{
	return nextWP;
}

Vector3 Waypoint::GetPos()
{
	return pos;
}