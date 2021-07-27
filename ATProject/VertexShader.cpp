#include "VertexShader.h"

VertexShader::VertexShader(Graphics& graphics, const std::wstring& directory)
{
	D3DReadFileToBlob(directory.c_str(), &ptrBCBlob);
	GetDevice(graphics)->CreateVertexShader(ptrBCBlob->GetBufferPointer(),
		ptrBCBlob->GetBufferSize(), nullptr, &ptrVShader);
}

void VertexShader::Bindable(Graphics& graphics) noexcept
{
	GetCont(graphics)->VSSetShader(ptrVShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetByteCode() const noexcept
{
	return ptrBCBlob.Get();
}