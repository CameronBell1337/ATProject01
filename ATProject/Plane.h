#include <vector>
#include <array>
#include "IndexedTriList.h"
#include "MathC.h"

class Plane
{
public:
	template<class V>
	static IndexTriList<V> MakeTesselated(int divX, int divY)
	{
		constexpr float w = 2.0f;
		constexpr float h = 2.0f;
		const int numVertX = divX + 1;
		const int numVertY = divY + 1;
		std::vector<V> vertices(numVertX * numVertY);
		{
			const float sideX = w / 2.0f;
			const float sideY = h / 2.0f;
			const float divisionSize_x = w / float(divX);
			const float divisionSize_y = h / float(divY);
			const auto bottomLeft = DirectX::XMVectorSet(-sideX, -sideY, 0.0f, 0.0f);

			for (int y = 0, i = 0; y < numVertY; y++)
			{
				const float posY = float(y) * divisionSize_y;
				for (int x = 0; x < numVertX; x++, i++)
				{
					const auto v = DirectX::XMVectorAdd(
						bottomLeft,
						DirectX::XMVectorSet(float(x) * divisionSize_x, posY, 0.0f, 0.0f)
					);
					DirectX::XMStoreFloat3(&vertices[i].pos, v);
				}
			}
		}

		std::vector<unsigned short> indices;
		indices.reserve(sqr(divX * divY) * 6);
		{
			const auto xy = [numVertX](size_t x, size_t y)
			{
				return (unsigned short)(y * numVertX + x);
			};
			for (size_t y = 0; y < divY; y++)
			{
				for (size_t x = 0; x < divX; x++)
				{
					const std::array<unsigned short, 4> iArray =
					{ xy(x,y),xy(x + 1,y),xy(x,y + 1),xy(x + 1,y + 1) };
					indices.push_back(iArray[0]);
					indices.push_back(iArray[2]);
					indices.push_back(iArray[1]);
					indices.push_back(iArray[1]);
					indices.push_back(iArray[2]);
					indices.push_back(iArray[3]);
				}
			}
		}

		return{ std::move(vertices),std::move(indices) };
	}
	template<class V>
	static IndexTriList<V> create()
	{
		return MakeTesselated<V>(1, 1);
	}
};
