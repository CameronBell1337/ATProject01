#pragma once
#include "Bindable.h"

class Topology : public Bind
{
public:
	Topology(Graphics& graphics, D3D11_PRIMITIVE_TOPOLOGY type_);
	void Bindable(Graphics& graphics) noexcept override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;

};