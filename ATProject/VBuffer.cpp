#include "VBuffer.h"

void VertexBuffer::Bindable(Graphics& graphics) noexcept
{
	const UINT offset = 0u;

	GetCont(graphics)->IASetVertexBuffers(0u, 1u,
		ptrVBuffer.GetAddressOf(), &stride, &offset);
}