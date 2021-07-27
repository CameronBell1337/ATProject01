#include "KeyboardHandler.h"


bool Keyboard::IsKeyPressed(unsigned char v_key) const noexcept
{
	return keyStates[v_key];
}

bool Keyboard::getKeyPressed(unsigned char v_key) const noexcept
{
	return keyStates[v_key] && keyStates[v_key] != oldKeyStates[v_key];
}

bool Keyboard::getKeyReleased(unsigned char v_key) const noexcept
{
	return keyStates[v_key] && keyStates[v_key] != oldKeyStates[v_key];
}

//Get inputs
Keyboard::Input Keyboard::GetKeyInput() noexcept
{
	if (keyBuffer.size() > 0u)
	{
		Keyboard::Input event = keyBuffer.front();
		keyBuffer.pop();
		return event;
	}
	return Keyboard::Input();
}

char Keyboard::GetCharInput() noexcept
{
	if (charBuffer.size() > 0u)
	{
		unsigned char char_key_code = charBuffer.front();
		charBuffer.pop();
		return char_key_code;
	}
	return 0;
}

//Checks if there is anything currently in Queue
bool Keyboard::IsKeyQEmpty() const noexcept
{
	return keyBuffer.empty();
}

bool Keyboard::IsCharQEmpty() const noexcept
{
	return charBuffer.empty();
}

//Clear individual Inputs
void Keyboard::ClearKey() noexcept
{
	keyBuffer = std::queue<Input>();
}

void Keyboard::ClearChar() noexcept
{
	charBuffer = std::queue<char>();
}

//Clears all inputs
void Keyboard::ClearAll() noexcept
{
	ClearKey();
	ClearChar();
}

//Repeat controls
bool Keyboard::CheckRepeatState()  const noexcept
{
	return IsRepeatEnabled;
}

void Keyboard::AllowRepeatInputs() noexcept
{
	IsRepeatEnabled = true;
}

void Keyboard::RevokeRepeatInputs() noexcept
{
	IsRepeatEnabled = false;
}

//Input state
void Keyboard::OnKeyDown(unsigned char v_key) noexcept
{
	//Checks if last pressed key is being pressed
	keyStates[v_key] = true;
	keyBuffer.push(Keyboard::Input(Keyboard::Input::EventType::pressed, v_key));
	ClampBuffer(keyBuffer);
}

void Keyboard::OnKeyUp(unsigned char v_key) noexcept
{
	//Checks if last pressed key is being released
	keyStates[v_key] = false;
	keyBuffer.push(Keyboard::Input(Keyboard::Input::EventType::released, v_key));
	ClampBuffer(keyBuffer);
}

void Keyboard::OnChar(char txt) noexcept
{
	charBuffer.push(txt);
	ClampBuffer(charBuffer);
}

void Keyboard::ClearKeyStates() noexcept
{
	keyStates.reset();
}

void Keyboard::endFrame() noexcept
{
	oldKeyStates = keyStates;
}

//Check if queues are higher than max buffer
template<typename T>
void Keyboard::ClampBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > bufferAmount)
	{
		buffer.pop();
	}


}