#pragma once
#include "Objects.h"
#include "Data.h"
#include "Waypoint.h"

class Wave : public Objects
{
public:
	Wave(Waypoint* initWP);
	void Update(Data* data) override;
	

	void Timer();
	void Spawn(Data* data);
	float ChangeRoundTimer(float dt);
private:

	float waitTimer;
	float roundTimer = 1.0f;

	bool toggle = false;

	

	Waypoint* firstWP = nullptr;

	Vector3 spawnWP;




};
