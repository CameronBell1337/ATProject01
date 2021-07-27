#pragma once
#include "Bindable.h"
#include <array>
#include <optional>


	/*class Blender : public Bind
	{
	public:
		Blender(Graphics& gfx, bool blending, std::optional<float> factor = {});
		void Bindable(Graphics& gfx) noexcept override;
		void SetFactor(float factor) noxnd;
		float GetFactor() const noxnd;
		static std::shared_ptr<Blender> Resolve(Graphics& gfx, bool blending, std::optional<float> factor = {});
		static std::string GenerateUID(bool blending, std::optional<float> factor);
		std::string GetUID() const noexcept override;
	protected:
		Microsoft::WRL::ComPtr<ID3D11BlendState> ptrBlender;
		bool blending;
		std::optional<std::array<float, 4>> factors;
	};/**/


