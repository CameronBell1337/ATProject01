#pragma once
#include "Drawables.h"
#include "IBuffer.h"


//Base class for static objects
template<class T>
class DrawableBase : public Draw
{
public:
	static void AddStaticBind(std::unique_ptr<Bind> bind) noexcept
	{
		sBinds.push_back(std::move(bind));
	}
	void AddStaticIBuffer(std::unique_ptr<IndexBuffer> i_buffer) noexcept
	{
		ptrIBuffer = i_buffer.get();
		sBinds.push_back(std::move(i_buffer));
	}
	void SetStaticIndex() noexcept
	{
		for (const auto& b : sBinds)
		{
			if (const auto ptr = dynamic_cast<IndexBuffer*>(b.get()))
			{
				ptrIBuffer = ptr;
				return;
			}
		}
	}

	static bool isStaticInit() noexcept
	{
		return !sBinds.empty();
	}

	const std::vector<std::unique_ptr<Bind>>& GetSBinds() const noexcept
	{
		return sBinds;
	}

private:
	
	static std::vector<std::unique_ptr<Bind>> sBinds;
};

template<class T>
std::vector<std::unique_ptr<Bind>> DrawableBase<T>::sBinds;
