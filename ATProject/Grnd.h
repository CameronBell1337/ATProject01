#pragma once
#include "DrawbaleBase.h"

class TowerBase;

//Ground of Map
class Grnd : public DrawableBase<Grnd>
{
public:
	Grnd(Graphics& graphics, DirectX::XMFLOAT3 colour);
	void Update(float dt) noexcept override {};

	void PlaceTowerOnTile(TowerBase* tower);
	TowerBase* GetTowerOnTile();
	//DirectX::XMMATRIX TransformM() const noexcept override;
private:

	
	TowerBase* occupyingTower = nullptr;

};