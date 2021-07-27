#include "TransformCBuffer.h"

TCBuffer::TCBuffer(Graphics& graphics, const Draw& p_, UINT slot)
	:  p(p_)
{
	if (!vcBuff)
	{
		vcBuff = std::make_unique<VConstBuff<DirectX::XMMATRIX>>(graphics, slot);
	}
}

void TCBuffer::Bindable(Graphics& graphics) noexcept
{
	
	vcBuff->Update(graphics,
		DirectX::XMMatrixTranspose(
			p.TransformM() * graphics.GetCam()* graphics.GetProjectionM()
		));
	

	vcBuff->Bindable(graphics);
}

std::unique_ptr<VConstBuff<DirectX::XMMATRIX>> TCBuffer::vcBuff;