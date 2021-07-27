#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <optional>
#include <memory>

#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "GraphicsHandler.h"

class WindowHandler
{
public:
	WindowHandler(int w, int h, const char* wndName);
	~WindowHandler();
	WindowHandler(const WindowHandler&) = delete;
	WindowHandler& operator=(const WindowHandler&) = delete;

	void ChangeWndTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	Graphics& Gfx();

	Keyboard kbd;
	Mouse mouse;

private:
	//singleton which manages reg & cleanup of winClass
	class WindowClass
	{
	public:
		static const char* GetWindowName() noexcept;
		static HINSTANCE GetInst() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* CLASS_NAME = "A GAME ENGINE!";
		static WindowClass wndClass;
		HINSTANCE hInst;



	};

	static LRESULT CALLBACK MsgSetup(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) noexcept;
	static LRESULT CALLBACK HandleMsgDispatch(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) noexcept;
	LRESULT MsgHandler(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) noexcept;

	HWND hwnd;
	std::unique_ptr<Graphics> ptrGfx;
	int w;
	int h;

};