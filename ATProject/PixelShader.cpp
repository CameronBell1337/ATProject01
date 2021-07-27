#include "PixelShader.h"


PixelShader::PixelShader(Graphics& graphics, const std::wstring& directory)
{
	Microsoft::WRL::ComPtr<ID3DBlob> ptrBlob;

	D3DReadFileToBlob(directory.c_str(), &ptrBlob);
	GetDevice(graphics)->CreatePixelShader(ptrBlob->GetBufferPointer(),
		ptrBlob->GetBufferSize(), nullptr, &ptrPxlShader);
}

void PixelShader::Bindable(Graphics& graphics) noexcept
{
	GetCont(graphics)->PSSetShader(ptrPxlShader.Get(), nullptr, 0u);
}