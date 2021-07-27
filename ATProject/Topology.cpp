#include "Topology.h"

Topology::Topology(Graphics& graphics, D3D11_PRIMITIVE_TOPOLOGY type_)
	: type(type_)
{
}

void Topology::Bindable(Graphics& graphics) noexcept
{
	GetCont(graphics)->IASetPrimitiveTopology(type);
}