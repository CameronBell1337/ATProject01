#include <vector>
#include <DirectXMath.h>

template<class T>
class IndexTriList
{
	
public:
	

	IndexTriList() = default;
	IndexTriList(std::vector<T> v_index, std::vector<unsigned short> i_index)
		:
		_verts(std::move(v_index)),
		_indices(std::move(i_index))
	{}

	void Transform(DirectX::FXMMATRIX _m)
	{
		for (auto& v : _verts)
		{
			const DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&v.pos);
			DirectX::XMStoreFloat3(&v.pos, DirectX::XMVector3Transform(pos, _m));
		}
	}

	std::vector<T> _verts;
	std::vector<unsigned short> _indices;
private:

};