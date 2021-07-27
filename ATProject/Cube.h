#pragma once
#include "IndexedTriList.h"
#include <DirectXMath.h>
#include "MathC.h"

class Cube
{
public:
	template<class V>
	static IndexTriList<V> create()
	{
		constexpr float s = 1.0f / 2.0f;

		std::vector<DirectX::XMFLOAT3> verts;
		verts.emplace_back(-s, -s, -s);
		verts.emplace_back(s, -s, -s);
		verts.emplace_back(-s, s, -s);
		verts.emplace_back(s, s, -s);
		verts.emplace_back(-s, -s, s);
		verts.emplace_back(s, -s, s);
		verts.emplace_back(-s, s, s);
		verts.emplace_back(s, s, s);

		std::vector<V> _verts(verts.size());
		for (size_t i = 0; i < verts.size(); i++)
		{
			_verts[i].pos = verts[i];
		}
		return{
			std::move(_verts),{
				0,2,1, 2,3,1,
				1,3,5, 3,7,5,
				2,6,3, 3,6,7,
				4,5,7, 4,7,6,
				0,4,2, 2,4,6,
				0,1,4, 1,5,4
			}
		};

	}
};