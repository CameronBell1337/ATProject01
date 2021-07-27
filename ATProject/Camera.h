#include "GraphicsHandler.h"
#include "Map.h"


class Camera
{
public:
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void UpdateCam(DirectX::XMFLOAT3 translation) noexcept;
	void ResetCam() noexcept;
	Camera() noexcept;


private:
	
	//world space
	DirectX::XMFLOAT3 pos;
	Map* map;
	
	//camera origin & orientation
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	float camMoveSpeed = 12.0f;
};
