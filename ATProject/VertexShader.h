#pragma once
#include "Bindable.h"

class VertexShader : public Bind
{
public:
	VertexShader(Graphics& graphics, const std::wstring& directory);
	void Bindable(Graphics& graphics) noexcept override;
	ID3DBlob* GetByteCode() const noexcept;
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> ptrBCBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> ptrVShader;
};