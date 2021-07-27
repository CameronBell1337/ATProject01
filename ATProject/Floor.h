#include "DrawbaleBase.h"

class Floor : public DrawableBase<Floor>
{
public:
	Floor(Graphics& graphics, std::mt19937& rng,
		std::uniform_real_distribution<float>& a_d,
		std::uniform_real_distribution<float>& d_d,
		std::uniform_real_distribution<float>& o_d,
		std::uniform_real_distribution<float>& r_d,
		std::uniform_int_distribution<int>& divX,
		std::uniform_int_distribution<int>& divY);

	void Update(float dt) noexcept override;
	DirectX::XMMATRIX TransformM() const noexcept override;

private:

	//Position 
	float origin;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;

	//Speed of obj from centre point
	float rollSpeed;
	float pitchSpeed;
	float yawSpeed;

	//Speed of obj in world space
	float ttaSpeed;
	float phiSpeed;
	float chiSpeed;


};