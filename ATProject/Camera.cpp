#include "Camera.h"
#include <algorithm>
#include "MathC.h"


namespace dx = DirectX;
Camera::Camera() noexcept
{
	ResetCam();
}

void Camera::ResetCam() noexcept
{
	float x = ((0.0f - -(map->mapW - 1.0f)) / 2.0f) + -(map->mapW - 1.0f);
	float y = ((0.0f - -(map->mapH - 2.0f)) / 2.0f) + -(map->mapH - 2.0f);
	pos = { -x,-y,-20.f };
}
DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{

	using namespace dx;

	const DirectX::XMVECTOR forward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	const auto lookV = DirectX::XMVector3Transform(forward, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f));

	const auto camPos = DirectX::XMLoadFloat3(&pos);
	const auto camTarget = camPos + lookV;

	return DirectX::XMMatrixLookAtLH(camPos, camTarget, DirectX::XMVectorSet(0.0f,1.0f,0.0f,0.0f));
}

void Camera::Rotate(float dx, float dy) noexcept
{
	yaw = wrap_angle(yaw + dx * rotationSpeed);
	pitch = std::clamp(pitch + dy * rotationSpeed, -_pi / 2.0f, _pi / 2.0f);
}

void Camera::UpdateCam(DirectX::XMFLOAT3 translation) noexcept
{
	DirectX::XMStoreFloat3(&translation, DirectX::XMVector3Transform(
		DirectX::XMLoadFloat3(&translation),
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixScaling(camMoveSpeed, camMoveSpeed, camMoveSpeed)));

	pos = {
		pos.x + translation.x,
		pos.y + translation.y,
		pos.z + translation.z
	};

	pos.x = std::clamp(pos.x, 15.0f, (float)map->mapW - 16);
	pos.y = std::clamp(pos.y, 10.0f, (float)map->mapH - 11);
	pos.z = std::clamp(pos.z, -20.0f, -15.0f);

}