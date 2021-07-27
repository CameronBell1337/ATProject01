#pragma once
#include "Bindable.h"

class VertexBuffer : public Bind
{
public:
	template<class V>
	VertexBuffer(Graphics& graphics, const std::vector<V>& verts)
		: stride(sizeof(V))
	{
		D3D11_BUFFER_DESC v_b_d = {};
		v_b_d.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		v_b_d.Usage = D3D11_USAGE_DEFAULT;
		v_b_d.CPUAccessFlags = 0u;
		v_b_d.MiscFlags = 0u;
		v_b_d.ByteWidth = UINT(sizeof(V) * verts.size());
		v_b_d.StructureByteStride = sizeof(V);
		D3D11_SUBRESOURCE_DATA v_s_d = {};
		v_s_d.pSysMem = verts.data();

		GetDevice(graphics)->CreateBuffer(&v_b_d, &v_s_d, &ptrVBuffer);
	}

	void Bindable(Graphics& graphics) noexcept override;
protected:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> ptrVBuffer;
};