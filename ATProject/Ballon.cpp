#include "Ballon.h"
#include "Box.h"
#include "Loon.h"
#include "GrndSelector.h"
#include <random>
#include <sstream>
#include <string.h>
#include <mutex>

Ballon::Ballon(Graphics& graphics, Waypoint* initWP, Vector3 init_pos)
{
	int test = 0;
	float randomRange = (float)rand() / (float)RAND_MAX;

	
	float moveSpeedMulti = minRangeSpeed + randomRange * (maxRangeSpeed - minRangeSpeed);
	float healthMulti = minHPRange + randomRange * (maxHPRange - minHPRange);
	ballonColour = {rangeColourX, rangeColourY , rangeColourZ };
	m = new Loon(graphics, ballonColour);
	m->SetScale(Vector3(0.5f,0.5f,0.5f));
	init_pos.z = 1.0f;
	init_pos.x = -1;
	SetPos(init_pos);
	currentWP = initWP;
	
	currentHP = healthMulti;
	//If HP is high lower speed for balance
	moveSpeed =  (currentHP > 40.0f ? (moveSpeedMulti / 2.0f): (moveSpeedMulti * 3.0f));


}

void Ballon::Update(Data* data)
{
	movement(data->dT);


}

void Ballon::movement(float dt)
{
	Vector3 distFromWP = currentWP->GetPos() - GetPos();
	Vector3 direction = distFromWP;

	direction.normalise();
	direction = direction * (moveSpeed *  dt);
	//TODO WAYPOINTS

	if (direction.magnitude() >= distFromWP.magnitude())
	{
		direction = distFromWP;
		currentWP = currentWP->GetNextWP();

		if (currentWP == nullptr)
		{
			//Delete ballon after it has reached last waypoint
			Objects::DestroyObj(this);
		}
	}
	//Set ballon position 
	SetPos(GetPos() + direction);
}


float Ballon::GetMaxHP() const
{
	return maxHP;
}
float Ballon::GetCurrentHP()
{
	return currentHP;
}

void Ballon::TakeDamage(Data* data, float dmgAmount)
{
	currentHP -= (int)dmgAmount;

	if (currentHP <= 0)
	{
		
		Objects::DestroyObj(this);
		
	}


}

void Ballon::GivePoints(Data* data)
{
	if (destroyed == true)
	{
		data->points = data->points + 10;
		destroyed = false;
	}
}