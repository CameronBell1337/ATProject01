#include "GraphicsHandler.h"
#include <sstream>
#include <d3dcompiler.h>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;
namespace dxM = DirectX;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")


Graphics::Graphics(HWND hwnd)
{

	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	UINT swapCreateFlags = 0u;

	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&ptrSwapChain,
		&ptrDevice,
		nullptr,
		&ptrContext);

	//Allow for texture subresource in the swapchain
	wrl::ComPtr<ID3D11Resource> ptrBBuffer = nullptr;
	ptrSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &ptrBBuffer);
	ptrDevice->CreateRenderTargetView(ptrBBuffer.Get(), nullptr, &ptrTarget);

	//depth stencil state
	D3D11_DEPTH_STENCIL_DESC dsD = {};
	dsD.DepthEnable = TRUE;
	dsD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsD.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> ptrDSState;
	ptrDevice->CreateDepthStencilState(&dsD, &ptrDSState);

	// bind depth state
	ptrContext->OMSetDepthStencilState(ptrDSState.Get(), 1u);

	//Create depth Stencil Texture
	wrl::ComPtr<ID3D11Texture2D> ptrDepS;
	D3D11_TEXTURE2D_DESC dD = {};
	dD.Width = 1280;
	dD.Height = 720;
	dD.MipLevels = 1u;
	dD.ArraySize = 1u;
	dD.Format = DXGI_FORMAT_D32_FLOAT;
	dD.SampleDesc.Count = 1u;
	dD.SampleDesc.Quality = 0u;
	dD.Usage = D3D11_USAGE_DEFAULT;
	dD.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	ptrDevice->CreateTexture2D(&dD, nullptr, &ptrDepS);

	//Create view of dst
	D3D11_DEPTH_STENCIL_VIEW_DESC dDVS = {};
	dDVS.Format = DXGI_FORMAT_D32_FLOAT;
	dDVS.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dDVS.Texture2D.MipSlice = 0u;
	ptrDevice->CreateDepthStencilView(ptrDepS.Get(), &dDVS, &ptrDepthV);

	//bind depth Stensil
	ptrContext->OMSetRenderTargets(1u, ptrTarget.GetAddressOf(), ptrDepthV.Get());

	//Configure the viewport
	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	ptrContext->RSSetViewports(1u, &vp);

}

void Graphics::EndFrame()
{
	ptrSwapChain->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b) noexcept
{
	const float colour[] = { r,g,b, 1.0f };
	ptrContext->ClearRenderTargetView(ptrTarget.Get(), colour);
	ptrContext->ClearDepthStencilView(ptrDepthV.Get(),D3D11_CLEAR_DEPTH,1.0f, 0);
}

void Graphics::DrawIndexed(UINT dCount) noexcept
{
	ptrContext->DrawIndexed(dCount, 0u, 0u);
}

void Graphics::SetProjectionM(DirectX::FXMMATRIX p) noexcept
{
	projection = p;
}

DirectX::XMMATRIX Graphics::GetProjectionM() const noexcept
{
	return projection;
}

void Graphics::SetCamera(DirectX::FXMMATRIX _cam) noexcept
{
	camera = _cam;
}

DirectX::XMMATRIX Graphics::GetCam() const noexcept
{
	return camera;
}

//Old
void Graphics::DrawC(float angle, float x, float y)
{
	struct Vertex
	{
		struct
		{
			float x, y, z;
		}pos;
	};

	//Create VBuffer for 2d shapes
	Vertex verts[] =
	{
		  //X     Y	   Z  
		 {-1.0f,-1.0f,-1.0f},
		 {1.0f,-1.0f,-1.0f},
		 {-1.0f,1.0f,-1.0f},
		 {1.0f,1.0f,-1.0f},
		 {-1.0f,-1.0f,1.0f},
		 {1.0f,-1.0f,1.0f},
		 {-1.0f,1.0f,1.0f},
		 {1.0f,1.0f,1.0f},
	};

	wrl::ComPtr<ID3D11Buffer> ptrVertBuffer;

	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(verts);
	bd.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = verts;

	ptrDevice->CreateBuffer(&bd, &sd, &ptrVertBuffer);

	//Bind VBuffer to the pLine
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	ptrContext->IASetVertexBuffers(0u, 1u, ptrVertBuffer.GetAddressOf(), &stride, &offset);

	//create index buffer
	const unsigned short indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4

	};
	wrl::ComPtr<ID3D11Buffer> ptrIndexBuffer;
	D3D11_BUFFER_DESC i_b_d = {};
	i_b_d.BindFlags = D3D11_BIND_INDEX_BUFFER;
	i_b_d.Usage = D3D11_USAGE_DEFAULT;
	i_b_d.CPUAccessFlags = 0u;
	i_b_d.MiscFlags = 0u;
	i_b_d.ByteWidth = sizeof(indices);
	i_b_d.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {}; //Indices subresource data
	isd.pSysMem = indices;
	ptrDevice->CreateBuffer(&i_b_d, &isd, &ptrIndexBuffer);

	//Bind index buffer
	ptrContext->IASetIndexBuffer(ptrIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	//Const Buffer for Transformation matix
	struct ConstBuffer
	{
		dxM::XMMATRIX transform;
	};
	const ConstBuffer c_b =
	{
		{
			dxM::XMMatrixTranspose(
				dxM::XMMatrixRotationZ(angle) *
				dxM::XMMatrixRotationX(angle)*
				dxM::XMMatrixTranslation(x, 0.0f, y + 7.0f) *
				dxM::XMMatrixPerspectiveLH(1.0f, 3.0f/4.0f, 0.5f, 10.0f)
			)
		}
	};
	wrl::ComPtr<ID3D11Buffer> ptrConstBuffer;
	D3D11_BUFFER_DESC c_b_d;
	c_b_d.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	c_b_d.Usage = D3D11_USAGE_DYNAMIC;
	c_b_d.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	c_b_d.MiscFlags = 0u;
	c_b_d.ByteWidth = sizeof(c_b);
	c_b_d.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &c_b;
	ptrDevice->CreateBuffer(&c_b_d, &csd, &ptrConstBuffer);

	//Bind Const Buffer
	ptrContext->VSSetConstantBuffers(0u, 1u, ptrConstBuffer.GetAddressOf());

	//Checks For the cubes FC
	struct ConstBufferFC
	{
		struct
		{
			float r, g, b, a;
		}face_colour[6];
	};
	const ConstBufferFC c_b_2 =
	{
		{ //RGB
			{0.5f,1.0f,0.0f},
			{1.0f,1.0f,0.0f},
			{0.7f,0.2f,0.6f},
			{1.0f,0.0f,0.0f},
			{1.0f,1.0f,0.0f},
			{0.5f,0.5f,0.0f},
		}
	};
	wrl::ComPtr<ID3D11Buffer> ptrConstBufferFC;
	D3D11_BUFFER_DESC c_b_d2;
	c_b_d2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	c_b_d2.Usage = D3D11_USAGE_DEFAULT;
	c_b_d2.CPUAccessFlags = 0u;
	c_b_d2.MiscFlags = 0u;
	c_b_d2.ByteWidth = sizeof(c_b_2);
	c_b_d2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA cbd2 = {};
	cbd2.pSysMem = &c_b_2;
	ptrDevice->CreateBuffer(&c_b_d2, &cbd2, &ptrConstBufferFC);

	ptrContext->PSSetConstantBuffers(0u, 1u, ptrConstBufferFC.GetAddressOf());


	//Create pxlShader
	wrl::ComPtr<ID3D11PixelShader> ptrPixelShader;
	wrl::ComPtr<ID3DBlob> ptrBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &ptrBlob);
	ptrDevice->CreatePixelShader(ptrBlob->GetBufferPointer(),ptrBlob->GetBufferSize(),nullptr, &ptrPixelShader);

	//Bind pxlShader
	ptrContext->PSSetShader(ptrPixelShader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11VertexShader> ptrVertShader;
	D3DReadFileToBlob(L"VertexShader.cso", &ptrBlob);
	ptrDevice->CreateVertexShader(ptrBlob->GetBufferPointer(),
		ptrBlob->GetBufferSize(),
		nullptr,
		&ptrVertShader);
	ptrContext->VSSetShader(ptrVertShader.Get(),
		nullptr,
		0u);

	//input layout for 2D
	wrl::ComPtr<ID3D11InputLayout> ptrInputLayout;
	const D3D11_INPUT_ELEMENT_DESC i_e_d[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	ptrDevice->CreateInputLayout(i_e_d, (UINT)std::size(i_e_d),
		ptrBlob->GetBufferPointer(),
		ptrBlob->GetBufferSize(),
		&ptrInputLayout);

	//Bind Vertex layout
	ptrContext->IASetInputLayout(ptrInputLayout.Get());

	//Bind Render target
	//ptrContext->OMSetRenderTargets(1u, ptrTarget.GetAddressOf(), nullptr);

	ptrContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Configure the viewport
	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 960;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	ptrContext->RSSetViewports(1u, &vp);


	//ptrContext->Draw((UINT)std::size(verts), 0u);
	ptrContext->DrawIndexed((UINT)std::size(indices),0u, 0u);
}