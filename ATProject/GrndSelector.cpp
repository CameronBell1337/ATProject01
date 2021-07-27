#include "GrndSelector.h"
#include "Map.h"
#include "Grnd.h"
#include "Tower.h"
#include "DartTower.h"
#include "MathC.h"
#include "KeyboardHandler.h"
#include "Ballon.h"

#include <sstream>
#include <string.h>

GrndSelector::GrndSelector(Graphics& graphics)
{
	m = new Box(graphics, colours0);

	m->SetScale(Vector3(0.8f, 0.8f, 1.2f));
	m->SetRot(Vector3(0.0f, 0.0f, 0.0f));

	Vector3 pos;

	pos.x = 20;
	pos.y = 13;
	pos.z = 1.0f;
	
	SetPos(pos);


	roundTimer = 1;
}

void GrndSelector::Update(Data* data)
{
	auto deltaT = data->dT;
	Vector3 dist;
	const auto k_input = data->kbd;

	
	
	if (GetPos().x < 39 && GetPos().y < 22 && GetPos().x > 2 && GetPos().y> 2)
	{
		if (k_input->getKeyPressed(VK_UP))
		{
			dist.y++;
		}
		if (k_input->getKeyPressed(VK_DOWN))
		{
			dist.y--;


		}
		if (k_input->getKeyPressed(VK_LEFT))
		{
			dist.x--;
		}
		if (k_input->getKeyPressed(VK_RIGHT))
		{
			dist.x++;
			std::ostringstream oss;
			oss << "(" << "Test" << ")/n";
			//OutputDebugString(oss.str().c_str());
		}
		

		//Place Turret on current space
		if (k_input->getKeyPressed('F'))
		{
			Grnd* t = data->map->GetGrnd(GetPos());

			if (data->points > 0)
			{
				if (t->GetTowerOnTile() == nullptr)
				{
					//TODO Allow realtime colour changes
					data->map->SetColour(colours0);
					auto spwanTurret = new DartTower(*data->graphics, GetPos());
					Objects::CreateObj(spwanTurret);
					t->PlaceTowerOnTile(spwanTurret);
					data->points -= towerCost;

				}
			}
		}	
	}
	//Dirt way to stop grid going out of bounds and not being able to return
	if (GetPos().x == 2)
	{
		GetPos().x == 3;
		dist.x++;
	}
	if (GetPos().x == 39)
	{
		GetPos().x == 38;
		dist.x--;
	}

	if (GetPos().y == 2)
	{
		GetPos().y == 3;
		dist.y++;
	}
	if (GetPos().y == 22)
	{
		GetPos().y == 21;
		dist.y--;
	}
	frac += deltaT * 1.0f;
	Vector3 taretPos = GetPos() + dist;
	Vector3 test = taretPos;

	test.normalise();
	test* frac;
	Vector3 diff = Vector3(
		lerp(GetPos().x, taretPos.x, test.magnitude()),
		lerp(GetPos().y, taretPos.y, test.magnitude()),
		lerp(GetPos().z, taretPos.z, test.magnitude()));

	//updates the position of target tile
	SetPos(diff);
}

void GrndSelector::AddPoints(int amount)
{
	points += amount;
}

void GrndSelector::RemovePoints(int amount)
{
	points -= amount;
}