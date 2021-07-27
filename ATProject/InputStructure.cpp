#include "InputStructure.h"

InputStructure::InputStructure(Graphics& graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>&
	structure, ID3DBlob* ptrVSB)
{
	GetDevice(graphics)->CreateInputLayout(structure.data(), (UINT)structure.size(),
		ptrVSB->GetBufferPointer(), ptrVSB->GetBufferSize(),
		&ptrIStructure);
}

void InputStructure::Bindable(Graphics& graphics) noexcept
{
	GetCont(graphics)->IASetInputLayout(ptrIStructure.Get());
}