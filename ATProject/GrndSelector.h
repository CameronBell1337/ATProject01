#pragma once
#include "Objects.h"
#include "Data.h"
#include "Map.h"
#include "Waypoint.h"
#include "Wave.h"

class GrndSelector : public Objects
{
public:
	GrndSelector(Graphics& graphics);
	void Update(Data* data) override;
	Map* map;

	void AddPoints(int points);
	void RemovePoints(int points);

	Waypoint* initWP = nullptr;
	Vector3 WPPos;



	float timer;
	float roundTimer;
	int points = 100;

	int towerCost = 100;

	DirectX::XMFLOAT3 colours0 = { 0.64f,0.64f,0.64f };

	float frac;
};