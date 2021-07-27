#pragma once
#include "GrndSelector.h"
#include "Objects.h"
#include "Waypoint.h"
#include "Objects.h"

class Ballon : public Objects
{
public:
	//TODO - Add more ballon types
	Ballon(Graphics& graphics, Waypoint* initWP, Vector3 init_pos);
	void Update(Data* data) override;
	void TakeDamage(Data* data,float damageAm);

	float GetMaxHP() const;
	float GetCurrentHP();

private:

	void movement(float dt);
	void GivePoints(Data* data);

	DirectX::XMFLOAT3 ballonColour = { 0.56f, 0.31f,0.92f };

	GrndSelector* select;
	Waypoint* currentWP;
	float moveSpeed = 5.52f;
	float maxHP = 10.0f;
	float currentHP;

	//Ranges
	float minRangeSpeed = 1.0f;
	float maxRangeSpeed = 5.5f;

	float rangeColourX = (float)rand() / (float)RAND_MAX;
	float rangeColourY = (float)rand() / (float)RAND_MAX;
	float rangeColourZ = (float)rand() / (float)RAND_MAX;

	float minHPRange = 10.0f;
	float maxHPRange = 100.0f;

	bool destroyed = false;

};

