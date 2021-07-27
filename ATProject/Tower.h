#pragma once
#include "Objects.h"
#include "Box.h"
#include "Data.h"
#include "Ballon.h"
#include "GrndSelector.h"

class TowerBase : public Objects
{
public:
	TowerBase(Graphics& graphics, Vector3 coords, DirectX::XMFLOAT3 colour);
	void Update(Data* data) override;
	void DrawObj(Graphics* graphics) override;

	virtual void Shoot(Data* data) = 0;
	virtual void TargetBallon(Data* data) = 0;

	bool TargetIsValid(Data* data);
	Ballon* currentTrg = nullptr;

	float attackDamage;
	float targetRange;
	float maxDelay;

	float currentTime = 0;

private:
	Box box;
	DirectX::XMFLOAT3 towerColour = { 1.0f,0.0f,0.0f };
	
};