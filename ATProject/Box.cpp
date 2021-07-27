#include "Box.h"
#include "Includes.h"
#include "Cube.h"


Box::Box(Graphics& graphics, DirectX::XMFLOAT3 colour)
{

	if (!isStaticInit())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
		};
		const auto m = Cube::create<Vertex>();
		AddStaticBind(std::make_unique<VertexBuffer>(graphics, m._verts));

		auto p_v_s = std::make_unique<VertexShader>(graphics,
			L"VertexShader1.cso");
		auto pvs_b_c = p_v_s->GetByteCode();

		AddStaticBind(std::move(p_v_s));
		AddStaticBind(std::make_unique<PixelShader>(graphics,
			L"PixelShader.cso"));

		
		AddStaticIBuffer(std::make_unique<IndexBuffer>(graphics, m._indices));

		

		const std::vector<D3D11_INPUT_ELEMENT_DESC> i_e_d =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		};

		AddStaticBind(std::make_unique<InputStructure>(graphics, i_e_d, pvs_b_c));
		AddStaticBind(std::make_unique<Topology>(graphics, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetStaticIndex();
	}

	struct ConstBuffer2
	{
		struct
		{
			float r, g, b, a;
		}faceRGB[8];
	};
	const ConstBuffer2 c_b_2 =
	{
		{ //RGB
			{ colour.x,colour.y,colour.z },
			{ colour.x,colour.y,colour.z },
			{ colour.x,colour.y,colour.z },
			{ colour.x,colour.y,colour.z },
			{ colour.x,colour.y,colour.z },
			{ colour.x,colour.y,colour.z },
			{ colour.x,colour.y,colour.z },
			{ colour.x,colour.y,colour.z },
		}
	};

	AddBind(std::make_unique<PConstBuff<ConstBuffer2>>(graphics, c_b_2, 0u));

	AddBind(std::make_unique<TCBuffer>(graphics, *this));

}


