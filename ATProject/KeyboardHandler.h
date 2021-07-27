#pragma once
#include <queue>
#include <bitset>
#include <optional>

class Keyboard
{
	friend class WindowHandler; //allows WindowHandler access to private functions

public:
	class Input
	{
		public:
			enum class EventType
			{
				pressed,
				released,
				Invalid
			};

			Input() : type(EventType::Invalid), code(0u)
			{}
			Input(EventType type, unsigned char code) noexcept :type(type), code(code) {}

			bool IsDown() const noexcept
			{
				return type == EventType::pressed;
			}

			bool isUp() const noexcept
			{
				return type == EventType::released;
			}

			bool isValid() const noexcept
			{
				return type != EventType::Invalid;
			}

			unsigned char GetKeyCode() const noexcept
			{
				return code;
			}
	private:
		EventType type;
		unsigned char code;
	};

	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	//Input Events
	bool IsKeyPressed(unsigned char v_key) const noexcept;
	bool IsKeyQEmpty() const noexcept;
	bool IsCharQEmpty() const noexcept;

	Input GetKeyInput() noexcept;
	char GetCharInput() noexcept;


	void ClearKey() noexcept;
	void ClearChar() noexcept;
	void ClearAll() noexcept;

	void AllowRepeatInputs() noexcept;
	void RevokeRepeatInputs() noexcept;

	bool CheckRepeatState() const noexcept;

	bool getKeyPressed(unsigned char v_key) const noexcept;
	bool getKeyReleased(unsigned char v_key) const noexcept;

	void endFrame() noexcept;

private:

	void OnKeyDown(unsigned char v_key) noexcept;
	void OnKeyUp(unsigned char v_key) noexcept;
	void OnChar(char txt) noexcept; //For using character specific to the key
	void ClearKeyStates() noexcept;

	template<typename T>
	static void ClampBuffer(std::queue<T>& buffer) noexcept;

	static constexpr unsigned int keyAmount = 256u; //Max amount of vKeyCodes available
	static constexpr unsigned int bufferAmount = 16u;

	bool IsRepeatEnabled = false;

	std::queue<Input> keyBuffer;
	std::queue<char> charBuffer;
	std::bitset<keyAmount> keyStates;
	std::bitset<keyAmount> oldKeyStates;

};
