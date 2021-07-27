#pragma once
#include "Bindable.h"

template<typename T>
class ConstBuff : public Bind
{
public:
	void Update(Graphics& graphics, const T& consts)
	{
		D3D11_MAPPED_SUBRESOURCE m_s_r;
		GetCont(graphics)->Map(
			ptrConstBuff.Get(), 
			0u, 
			D3D11_MAP_WRITE_DISCARD, 
			0u, &m_s_r);

		//memcpy ( void * destination, const void * source, size_t num );
		//copy value of num bytes from location of pointer
		memcpy(m_s_r.pData, &consts, sizeof(consts));

		GetCont(graphics)->Unmap(ptrConstBuff.Get(), 0u);
	}
	ConstBuff(Graphics& graphics, const T& consts, UINT slot = 0u)
		:slot(slot)
	{
		D3D11_BUFFER_DESC c_b_d;
		c_b_d.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		c_b_d.Usage = D3D11_USAGE_DYNAMIC;
		c_b_d.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		c_b_d.MiscFlags = 0u;
		c_b_d.ByteWidth = sizeof(consts);
		c_b_d.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &consts;
		GetDevice(graphics)->CreateBuffer(&c_b_d, &csd, &ptrConstBuff);
	}
	ConstBuff(Graphics& graphics, UINT slot = 0u)
		: slot(slot)
	{
		D3D11_BUFFER_DESC c_b_d;
		c_b_d.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		c_b_d.Usage = D3D11_USAGE_DYNAMIC;
		c_b_d.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		c_b_d.MiscFlags = 0u;
		c_b_d.ByteWidth = sizeof(T);
		c_b_d.StructureByteStride = 0u;

		GetDevice(graphics)->CreateBuffer(&c_b_d, nullptr, &ptrConstBuff);
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> ptrConstBuff;
	UINT slot;
};

template<typename T>
class VConstBuff : public ConstBuff<T>
{
	using ConstBuff<T>::ptrConstBuff;
	using ConstBuff<T>::slot;
	using Bind::GetCont; // Get Context
public:
	using ConstBuff<T>::ConstBuff;
	void Bindable(Graphics& graphics) noexcept override
	{
		GetCont(graphics)->VSSetConstantBuffers(slot, 
			1u, 
			ptrConstBuff.GetAddressOf());
	}
};

template<typename T>
class PConstBuff : public ConstBuff<T>
{
	using ConstBuff<T>::ptrConstBuff;
	using ConstBuff<T>::slot;
	using Bind::GetCont; // Get Context
public:
	using ConstBuff<T>::ConstBuff;
	void Bindable(Graphics& graphics) noexcept override
	{
		GetCont(graphics)->PSSetConstantBuffers(slot,
			1u,
			ptrConstBuff.GetAddressOf());
	}
};
