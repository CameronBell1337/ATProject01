#pragma once
#include "Drawables.h"
#include "IBuffer.h"

Draw::Draw(Draw&& obj) noexcept :
	binds(std::move(obj.binds)),
	local_transform(obj.local_transform),
	pos({ obj.pos.x,obj.pos.y, obj.pos.z }),
	scale({obj.scale.x, obj.scale.y, obj.scale.z}),
	pitch(obj.pitch), yaw(obj.yaw), roll(obj.roll)
{}

void Draw::DrawObj(Graphics& graphics) const noexcept
{
	for (auto& b : binds)
	{
		b->Bindable(graphics);
	}

	for (auto& b : GetSBinds())
	{
		b->Bindable(graphics);
	}

	graphics.DrawIndexed(ptrIBuffer->DrawCount());
}

void Draw::AddBind(std::unique_ptr<Bind> bind) noexcept
{
	binds.push_back(std::move(bind));
}

void Draw::AddIBuffer(std::unique_ptr<IndexBuffer> iBuffer) noexcept
{
	ptrIBuffer = iBuffer.get();
	binds.push_back(std::move(iBuffer));
}

DirectX::XMMATRIX Draw::TransformM() const noexcept
{
	return local_transform *
		DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}

void Draw::SetPos(Vector3 _pos)
{
	pos.x = _pos.x;
	pos.y = _pos.y;
	pos.z = _pos.z;

}

void Draw::SetRot(Vector3 _rot)
{
	pitch = _rot.y;
	yaw = _rot.z;
	roll = _rot.x;
}

void Draw::SetScale(Vector3 _scale)
{
	scale.x = _scale.x;
	scale.y = _scale.y;
	scale.z = _scale.z;
}
