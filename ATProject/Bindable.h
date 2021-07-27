#pragma once
#include "GraphicsHandler.h"


class Bind
{
	public:
		virtual void Bindable(Graphics& graphics) noexcept = 0;
		virtual ~Bind() = default;
	protected:
		static ID3D11DeviceContext* GetCont(Graphics& graphics) noexcept;
		static ID3D11Device* GetDevice(Graphics& graphics) noexcept;
};