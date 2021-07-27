#pragma once
#include "MathC.h"
#include "IndexedTriList.h"
#include <DirectXMath.h>

class Sphere
{
public:
	template<class V>
	static IndexTriList<V> MakeTesselated(int latDiv, int longDiv)
	{
		constexpr float r = 1.0f;
		const auto b = DirectX::XMVectorSet(0.0f, 0.0f, r, 0.0f);
		const float lattitudeAngle = _pi / latDiv;
		const float longitudeAngle = 2.0f * _pi / longDiv;

		std::vector<V> vert;
		for (int iLat = 1; iLat < latDiv; iLat++)
		{
			const auto latB = DirectX::XMVector3Transform(
				b,
				DirectX::XMMatrixRotationX(lattitudeAngle * iLat)
			);
			for (int iLong = 0; iLong < longDiv; iLong++)
			{
				vert.emplace_back();
				auto v = DirectX::XMVector3Transform(
					latB,
					DirectX::XMMatrixRotationZ(longitudeAngle * iLong)
				);
				DirectX::XMStoreFloat3(&vert.back().pos, v);
			}
		}

		// add the cap vertices
		const auto top = (unsigned short)vert.size();
		vert.emplace_back();
		DirectX::XMStoreFloat3(&vert.back().pos, b);

		const auto bottom = (unsigned short)vert.size();
		vert.emplace_back();
		DirectX::XMStoreFloat3(&vert.back().pos, DirectX::XMVectorNegate(b));

		const auto calIndex = [latDiv, longDiv](unsigned short i, unsigned short iLong)
		{ return i * longDiv + iLong; };

		std::vector<unsigned short> indices;
		for (unsigned short i = 0; i < latDiv - 2; i++)
		{
			for (unsigned short j = 0; j < longDiv - 1; j++)
			{
				indices.push_back(calIndex(i, j));
				indices.push_back(calIndex(i + 1, j));
				indices.push_back(calIndex(i, j + 1));
				indices.push_back(calIndex(i, j + 1));
				indices.push_back(calIndex(i + 1, j));
				indices.push_back(calIndex(i + 1, j + 1));
			}
			indices.push_back(calIndex(i, longDiv - 1));
			indices.push_back(calIndex(i + 1, longDiv - 1));
			indices.push_back(calIndex(i, 0));
			indices.push_back(calIndex(i, 0));
			indices.push_back(calIndex(i + 1, longDiv - 1));
			indices.push_back(calIndex(i + 1, 0));
		}

		
		for (unsigned short j = 0; j < longDiv - 1; j++)
		{
			//top
			indices.push_back(top);
			indices.push_back(calIndex(0, j));
			indices.push_back(calIndex(0, j + 1));
			//bottom
			indices.push_back(calIndex(latDiv - 2, j + 1));
			indices.push_back(calIndex(latDiv - 2, j));
			indices.push_back(bottom);
		}
		
		//top
		indices.push_back(top);
		indices.push_back(calIndex(0, longDiv - 1));
		indices.push_back(calIndex(0, 0));
		//bottom
		indices.push_back(calIndex(latDiv - 2, 0));
		indices.push_back(calIndex(latDiv - 2, longDiv - 1));
		indices.push_back(bottom);

		return { std::move(vert),std::move(indices) };
	}
	template<class V>
	static IndexTriList<V> Create()
	{
		return MakeTesselated<V>(12, 24);
	}

};