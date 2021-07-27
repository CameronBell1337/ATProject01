#include "DartTower.h"
#include "Box.h"
#include <algorithm>
#include <array>
#include <iostream>
#include "Tower.h"



DartTower::DartTower(Graphics& graphics, Vector3 coords) : TowerBase(graphics, coords, dartTowerColour)
{
	//Setting Tower as Box
	m = new Box(graphics, dartTowerColour);
	m->SetScale(Vector3(0.8f, 0.8f, 1.2f));

	coords.z = 1.0f;
	SetPos(coords);

	attackDamage = 15.0f;
	maxDelay = 2.5f;
	targetRange = 3.0f;

}

void DartTower::Shoot(Data* data)
{
	//TODO Add bullet
	currentTrg->TakeDamage(data,attackDamage);

}

void DartTower::TargetBallon(Data* data)
{
	auto closestTarget = targetRange;
	Vector3 d;
	for (Objects* obj : *data->objs)
	{
		Ballon* loon = dynamic_cast<Ballon*>(obj);
		DartTower* numTowers = dynamic_cast<DartTower*>(obj);

		if (loon == nullptr)
		{
			//Check is tower doesnt already have a target
			continue;
		}

		//difference between baloon and tower
		d = loon->GetPos() - GetPos();
		float distFrom = d.magnitude();
		if (distFrom < closestTarget)
		{
			//Checks for closest target within range and reduces range
			closestTarget = distFrom;
			currentTrg = loon;
		}

		num = count(obj->GetObjList().begin(), obj->GetObjList().end(), numTowers);
		if (loon->GetCurrentHP() <= 0 && hadDestroyed == false)
		{
			data->points += 1;
			//data->points -= 10 * num;
			hadDestroyed = false;
			return;
		}

		data->points -= 10 * num;

	}
	if (closestTarget == 0)
	{
		
		currentTrg = nullptr;
		hadDestroyed = false;
		return;
	}

	
}