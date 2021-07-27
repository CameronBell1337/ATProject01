#pragma once
#include "Drawables.h"
#include "DrawbaleBase.h"

class Box : public DrawableBase<Box>
{
public:
	Box(Graphics& graphics, DirectX::XMFLOAT3 colour);
private:
	
};