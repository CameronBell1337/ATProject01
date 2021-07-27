#include "Tower.h"


TowerBase::TowerBase(Graphics& graphics, Vector3 coords, DirectX::XMFLOAT3 colour) : 
	box(graphics, colour)
{
	box.SetPos(coords);
}

void TowerBase::DrawObj(Graphics* graphics)
{
	if (m != nullptr)
	{
		m->DrawObj(*graphics);
	}
}

void TowerBase::Update(Data* data)
{
	currentTime += data->dT;
	if (!TargetIsValid(data))
	{
		return;
	}
	if (currentTime >= maxDelay)
	{
		Shoot(data);
		currentTime = 0.0f;
	}
}

bool TowerBase::TargetIsValid(Data* data)
{
	Vector3 distFrom;
	if (currentTrg == nullptr)
	{
		//Checks if there is no current target ballon and loops through
		TargetBallon(data);
		return currentTrg != nullptr;
	}
	//Calcuate distance between tower and ballon
	distFrom = currentTrg->GetPos() - GetPos();
	if (distFrom.magnitude() > targetRange)
	{
		TargetBallon(data);
	}
	return currentTrg != nullptr;
}
