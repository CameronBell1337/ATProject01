#include "MouseHandler.h"
#include <Windows.h>

std::pair<int, int> Mouse::GetMPos() const noexcept
{
	return { x_pos, y_pos };
}

//Get Mouse info
int Mouse::GetXPos() const noexcept
{
	return x_pos;
}
int Mouse::GetYPos() const noexcept
{
	return y_pos;
}

Mouse::Input Mouse::GetMouseInput() noexcept
{
	if (mBuffer.size() > 0u)
	{
		Mouse::Input mi = mBuffer.front();
		mBuffer.pop();
		return mi;
	}
	return Mouse::Input();
	
}


//Get if Mouse is withing app window
bool Mouse::IsCursorInBound() const noexcept
{
	return isInBound;
}

//Get current state of bools
bool Mouse::LeftMButtonPressed() const noexcept
{
	return isLeftMBDown;
}
bool Mouse::RightMButtonPressed() const noexcept
{
	return isRightMBDown;
}

bool Mouse::IsMWheelDown() const noexcept
{
	return isMWheelDown;
}

bool Mouse::IsMWheelUp() const noexcept
{
	return isMWheelUp;
}

void Mouse::ClearQueue() noexcept //Clears any mouse inputs queued
{
	mBuffer = std::queue<Input>();
}

//Enable/Disables input from the
void Mouse::AllowRawInput() noexcept
{
	rawInputEnabled = true;
}
void Mouse::RevokeRawInput() noexcept
{
	rawInputEnabled = false;
}
bool Mouse::CheckRawInputState() const noexcept
{
	return rawInputEnabled;
}

void Mouse::OnMoveMouse(int n_x_pos, int n_y_pos) noexcept
{
	x_pos = n_x_pos;
	y_pos = n_y_pos;

	mBuffer.push(Mouse::Input(Mouse::Input::EventType::move_mouse, *this));
	ClampMBuffer();
}


//Checks if Mouse is in Bounds
void Mouse::MouseEnterBound() noexcept
{
	isInBound = true;
	mBuffer.push(Mouse::Input(Mouse::Input::EventType::enter_bound, *this));
	ClampMBuffer();
}
void Mouse::MouseOutBound() noexcept
{
	isInBound = false;
	mBuffer.push(Mouse::Input(Mouse::Input::EventType::leave_bound, *this));
	ClampMBuffer();
}


//mouse Button Checks
void Mouse::LeftButtonDown(int x_pos, int y_pos) noexcept
{
	isLeftMBDown = true;
	mBuffer.push(Mouse::Input(Mouse::Input::EventType::l_b_pressed, *this));
	ClampMBuffer();
}
void Mouse::LeftButtonUp(int x_pos, int y_pos) noexcept
{
	isLeftMBDown = false;
	mBuffer.push(Mouse::Input(Mouse::Input::EventType::l_b_released, *this));
	ClampMBuffer();
}

void Mouse::RightButtonDown(int x_pos, int y_pos) noexcept
{
	isRightMBDown = true;
	mBuffer.push(Mouse::Input(Mouse::Input::EventType::r_b_pressed, *this));
	ClampMBuffer();
}
void Mouse::RightButtonUp(int x_pos, int y_pos) noexcept
{
	isRightMBDown = false;
	mBuffer.push(Mouse::Input(Mouse::Input::EventType::r_b_released, *this));
	ClampMBuffer();
}

//Mouse ScrollWheel
void Mouse::MWheelDown(int x, int y) noexcept
{
	mBuffer.push(Mouse::Input(Mouse::Input::EventType::m_wheel_down, *this));
	ClampMBuffer();
}
void Mouse::MWheelUp(int x, int y) noexcept
{
	mBuffer.push(Mouse::Input(Mouse::Input::EventType::m_wheel_up, *this));
	ClampMBuffer();
}
void Mouse::MWheelRaw(int x, int y, int raw) noexcept
{
	mWheelRaw += raw;

	while (mWheelRaw >= WHEEL_DELTA)
	{
		mWheelRaw -= WHEEL_DELTA;
		MWheelUp(x, y);
	}
	while (mWheelRaw <= -WHEEL_DELTA)
	{
		mWheelRaw += WHEEL_DELTA;
		MWheelDown(x, y);
	}

}

void Mouse::ClampMBuffer() noexcept
{
	while (mBuffer.size() > bufferAmount)
	{
		mBuffer.pop();
	}
}