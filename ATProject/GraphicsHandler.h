#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <memory>
#include <random>
#include <DirectXMath.h>
#include <d3dcompiler.h>

class Graphics
{
	friend class Bind;
public:
	Graphics(HWND hwnd);
	~Graphics() = default;

	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	void EndFrame();
	void ClearBuffer(float r, float g, float b) noexcept;
	void DrawC(float angle, float x, float y);

	void DrawIndexed(UINT count) noexcept;
	void SetProjectionM(DirectX::FXMMATRIX p) noexcept;
	DirectX::XMMATRIX GetProjectionM() const noexcept;

	void SetCamera(DirectX::FXMMATRIX _cam) noexcept;
	DirectX::XMMATRIX GetCam() const noexcept;
private:

	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;

	Microsoft::WRL::ComPtr<ID3D11Device> ptrDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> ptrSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> ptrContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> ptrTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> ptrDepthV;
};
