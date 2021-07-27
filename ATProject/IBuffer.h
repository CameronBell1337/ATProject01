#pragma once
#include "Bindable.h"

class IndexBuffer : public Bind
{
public:
	IndexBuffer(Graphics& graphics, const std::vector<unsigned short>& indices);
	void Bindable(Graphics& graphics) noexcept override;
	UINT DrawCount() const noexcept;

protected:
	UINT dCount;
	Microsoft::WRL::ComPtr<ID3D11Buffer> ptrIBuffer;

};