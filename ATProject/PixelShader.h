#pragma once
#include "Bindable.h"
#include <string>

class PixelShader : public Bind
{
public:
	PixelShader(Graphics& graphics, const std::wstring& directory);
	void Bindable(Graphics& graphics) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> ptrPxlShader;
};