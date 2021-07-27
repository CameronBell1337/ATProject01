#include "Bindable.h"

ID3D11Device* Bind::GetDevice(Graphics& graphics) noexcept
{
	return graphics.ptrDevice.Get();
}

ID3D11DeviceContext* Bind::GetCont(Graphics& graphics) noexcept
{
	return graphics.ptrContext.Get();
}
