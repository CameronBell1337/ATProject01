#pragma once
#include "GraphicsHandler.h"
#include <DirectXMath.h>
#include "IBuffer.h"
#include "Vector3.h"
#include <vector>

class Bind;

class Draw
{
	template<class T>
	friend class DrawableBase;
public:
	Draw() = default;
	Draw(const Draw&) = delete;
	Draw(Draw&& obj) noexcept;

	virtual DirectX::XMMATRIX TransformM() const noexcept;
	virtual void Update(float delta_time) noexcept {};
	virtual ~Draw() = default;

	void DrawObj(Graphics& graphics) const noexcept;

	void SetPos(Vector3 pos);
	void SetScale(Vector3 scale);
	void SetRot(Vector3 rot);

	void AddBind(std::unique_ptr<Bind> bind) noexcept;
	void AddIBuffer(std::unique_ptr<class IndexBuffer> iBuffer) noexcept;
private:
	virtual const std::vector<std::unique_ptr<Bind>>& GetSBinds() const noexcept = 0;
	const class IndexBuffer* ptrIBuffer = nullptr;
	const DirectX::XMMATRIX local_transform = DirectX::XMMatrixScaling(1, 1, 1);
	std::vector<std::unique_ptr<Bind>> binds;

	//pos, rot & scale
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 scale = { 1.0f,1.0f,1.0f };

	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

};