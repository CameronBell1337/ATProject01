#include "Wave.h"
#include "Ballon.h"
#include "KeyboardHandler.h"
#include "GrndSelector.h"
#include <sstream>
#include <string.h>

Wave::Wave(Waypoint* initWP)
{
	firstWP = initWP;
	Vector3 WP = initWP->GetPos();
	WP.x = -1.0f;
	WP.z = 1.0f;
	spawnWP = WP;
	//roundTimer;
}

void Wave::Update(Data* data)
{
	const auto k_input = data->kbd;

	if (k_input->getKeyPressed('E'))
	{
		if (!toggle)
		{
			toggle = true;
		}
		else
		{
			toggle = false;
		}
	}


	//waitTimer -= data->dT;
	roundTimer -= data->dT;
	if (toggle)
	{
		while (roundTimer <= 0)
		{

			Spawn(data);
			Timer();
			break;
		}
	}
}


void Wave::Spawn(Data* data)
{
	Ballon* newBallon = new Ballon(*data->graphics, firstWP, spawnWP);
	Objects::CreateObj(newBallon);
	roundTimer = 1.0f;
}

void Wave::Timer()
{
	roundTimer =  rand() / float(RAND_MAX);
	roundTimer = roundTimer * 1.75f;
}

float Wave::ChangeRoundTimer(float dt)
{
	
	return roundTimer -= dt;
}