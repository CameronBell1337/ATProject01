#pragma once
#include "Tower.h"

class DartTower : public TowerBase
{
public:
	DartTower(Graphics& graphics, Vector3 coords);
private:
	void Shoot(Data* data) override;
	void TargetBallon(Data* data) override;
	int num;
	bool hadDestroyed = false;
	DirectX::XMFLOAT3 dartTowerColour = { 1.0f,0.0f,0.0f };
};