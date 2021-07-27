#include "IBuffer.h"


void IndexBuffer::Bindable(Graphics& graphics) noexcept
{
	GetCont(graphics)->IASetIndexBuffer(ptrIBuffer.Get(),
		DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::DrawCount() const noexcept
{
	return dCount;
}


IndexBuffer::IndexBuffer(Graphics& graphics, 
	const std::vector<unsigned short>& indices) 
	: dCount((UINT)indices.size())
{
	D3D11_BUFFER_DESC i_b_d = {}; //IndexBufferDesc

	i_b_d.BindFlags = D3D11_BIND_INDEX_BUFFER;
	i_b_d.Usage = D3D11_USAGE_DEFAULT;
	i_b_d.CPUAccessFlags = 0u;
	i_b_d.MiscFlags = 0u;
	i_b_d.ByteWidth = UINT(dCount * sizeof(unsigned short));
	i_b_d.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA i_s_d = {};
	i_s_d.pSysMem = indices.data();
	GetDevice(graphics)->CreateBuffer(&i_b_d, &i_s_d, &ptrIBuffer);
}