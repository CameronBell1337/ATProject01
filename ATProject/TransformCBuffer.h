#pragma once
#include "CBuffer.h"
#include <DirectXMath.h>
#include "Drawables.h"

class TCBuffer : public Bind
{
public:
	TCBuffer(Graphics& graphics, const Draw& p_, UINT slot = 0u);
	void Bindable(Graphics& graphics) noexcept override;
private:
	
	static std::unique_ptr<VConstBuff<DirectX::XMMATRIX>> vcBuff;
	const Draw& p;
};