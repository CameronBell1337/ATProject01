#pragma once
#include <queue>
#include <optional>


class Mouse
{
	friend class WindowHandler;

public:
	class Input
	{

	public:
		enum class EventType
		{
			l_b_pressed,
			l_b_released,

			r_b_pressed,
			r_b_released,

			m_wheel_up,
			m_wheel_down,

			move_mouse,

			enter_bound,
			leave_bound,

			Invalid,

		};
		Input() noexcept
			:
			type(EventType::Invalid),
			IsLBDown(false),
			IsRBDown(false),
			x_pos(0),
			y_pos(0),
			MWHEELRAW(0)
		{}
		Input(EventType type, const Mouse& p) noexcept : type(type), IsLBDown(p.isLeftMBDown),
			IsRBDown(p.isRightMBDown), x_pos(p.x_pos), y_pos(p.y_pos), MWHEELRAW(p.mWheelRaw) {}

		EventType GetEventType() const noexcept
		{
			return type;
		}

		std::pair<int, int> GetMPos() const noexcept
		{
			return{ x_pos, y_pos };
		}

		int GetMPosX() const noexcept
		{
			return x_pos;
		}

		int GetMPosY() const noexcept
		{
			return y_pos;
		}

		bool LeftMButtonDown() const noexcept
		{
			return IsLBDown;
		}

		bool IsValid() const noexcept
		{
			return type != EventType::Invalid;
		}

		bool RightMButtonDown() const noexcept
		{
			return IsRBDown;
		}

		int GetMWheelRaw() const noexcept
		{
			return MWHEELRAW;
		}


	private:

		EventType type;

		bool IsLBDown;
		bool IsRBDown;

		int MWHEELRAW;

		int x_pos;
		int y_pos;

	};


	Mouse() = default;
	Mouse& operator=(const Mouse&) = delete;
	Mouse(const Mouse&) = delete;

	//Mouse Input Events
	bool IsCursorInBound() const noexcept; // Checks if the mouse has outside of the window
	bool LeftMButtonPressed() const noexcept;
	bool RightMButtonPressed() const noexcept;
	bool IsMWheelDown() const noexcept;
	bool IsMWheelUp() const noexcept;

	bool IsMouseQEmpty() const noexcept
	{
		return mBuffer.empty();
	}

	std::pair<int, int> GetMPos() const noexcept;

	Mouse::Input GetMouseInput() noexcept; //reads current input

	int GetXPos() const noexcept;
	int GetYPos() const noexcept;

	void ClearQueue() noexcept;
	void AllowRawInput() noexcept;
	void RevokeRawInput() noexcept;

	bool CheckRawInputState() const noexcept;

private:

	void OnMoveMouse(int x_pos, int y_pos) noexcept;
	//void OnRawInput(int r_x, int r_y) noexcept;

	void MouseOutBound() noexcept;
	void MouseEnterBound() noexcept;

	//Mouse Button Inputs
	void LeftButtonDown(int x_pos, int y_pos) noexcept;
	void LeftButtonUp(int x_pos, int y_pos) noexcept;

	void RightButtonDown(int x_pos, int y_pos) noexcept;
	void RightButtonUp(int x_pos, int y_pos) noexcept;

	void MWheelUp(int x, int y) noexcept;
	void MWheelDown(int x, int y) noexcept;
	void MWheelRaw(int x, int y, int raw) noexcept;

	void ClampMBuffer() noexcept;
	void ClampRawInputBuffer() noexcept;

	static constexpr unsigned int bufferAmount = 16u;

	int x_pos;
	int y_pos;
	int mWheelRaw = 0;

	bool isLeftMBDown = false;
	bool isRightMBDown = false;
	bool isInBound = false;
	bool rawInputEnabled = false;

	bool isMWheelDown = false;
	bool isMWheelUp = false;

	std::queue<Input> mBuffer;
	//std::queue<RawInput> rawInputBuffer;
};