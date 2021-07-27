#pragma once
#include "Bindable.h"

class InputStructure : public Bind
{
public:
	InputStructure(Graphics& graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>&
		structure, ID3DBlob* ptrVSB);
	void Bindable(Graphics& graphics) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> ptrIStructure;

};