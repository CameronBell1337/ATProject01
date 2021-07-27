#include "Plane.h"
#include "Includes.h"
#include "Floor.h"


Floor::Floor(Graphics& graphics, std::mt19937& rng,
	std::uniform_real_distribution<float>& a_d,
	std::uniform_real_distribution<float>& d_d,
	std::uniform_real_distribution<float>& o_d,
	std::uniform_real_distribution<float>& r_d,
	std::uniform_int_distribution<int>& divX,
	std::uniform_int_distribution<int>& divY)
	: origin(r_d(rng)),
	rollSpeed(float(2)), pitchSpeed(float(2)), yawSpeed(float(2)),
	phiSpeed(o_d(rng)), ttaSpeed(o_d(rng)), chiSpeed(o_d(rng)),
	chi(a_d(rng)), theta(a_d(rng)), phi(a_d(rng))
{
	if (!isStaticInit())
	{
		auto p_v_s = std::make_unique<VertexShader>(graphics, L"VertexShader1.cso");
		auto pvs_b_c = p_v_s->GetByteCode();

		AddStaticBind(std::move(p_v_s));
		AddStaticBind(std::make_unique<PixelShader>(graphics, L"PixelShader.cso"));

		struct PSConst
		{
			struct
			{
				float r, g, b, a;
				
			}faceRGB[8];
		};

		const PSConst c_b_2 =
		{
			{
				{ 1.0f,0.0f,1.0f },
				{ 1.0f,1.0f,0.0f },
				{ 1.0f,0.0f,1.0f },
				{ 1.0f,1.0f,0.0f },
				{ 1.0f,0.0f,1.0f },
				{ 1.0f,1.0f,0.0f },
				{ 1.0f,0.0f,1.0f },
				{ 1.0f,1.0f,0.0f },
			}
		};

		AddStaticBind(std::make_unique<PConstBuff<PSConst>>(graphics, c_b_2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> i_e_d =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		};

		AddStaticBind(std::make_unique<InputStructure>(graphics, i_e_d, pvs_b_c));
		AddStaticBind(std::make_unique<Topology>(graphics, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	struct vert
	{
		DirectX::XMFLOAT3 pos;
	};

	auto m = Plane::MakeTesselated<vert>(24, 24);

	m.Transform(DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f));

	AddBind(std::make_unique<VertexBuffer>(graphics, m._verts));
	AddIBuffer(std::make_unique<IndexBuffer>(graphics, m._indices));
	AddBind(std::make_unique<TCBuffer>(graphics, *this));


}

void Floor::Update(float dt) noexcept
{
	//Rotation
	roll += rollSpeed * dt;
	pitch += pitchSpeed * dt;
	yaw += yawSpeed * dt;

	//Transform pos
	theta += ttaSpeed * dt;
	phi += phiSpeed * dt;
	chi += chiSpeed * dt;
}

DirectX::XMMATRIX Floor::TransformM() const noexcept
{
	return 
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(origin, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}
