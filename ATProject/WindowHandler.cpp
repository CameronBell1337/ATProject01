#include "WindowHandler.h"
#include <string>
#include <sstream>
#include "resource.h"


WindowHandler::WindowClass WindowHandler::WindowClass::wndClass;

WindowHandler::WindowClass::WindowClass() noexcept : hInst(GetModuleHandle(nullptr))
{
	// Register WNDClass
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_OWNDC; //unique device context
	wndClass.lpfnWndProc = MsgSetup;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = GetInst(); //Instance Handler
	wndClass.hIcon = static_cast<HICON>(LoadImage(GetInst(), MAKEINTRESOURCE(IDI_ICON2),
		IMAGE_ICON, 32, 32, 0));
	wndClass.hCursor = nullptr;
	wndClass.hbrBackground = nullptr;
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = GetWindowName(); //Window Name
	wndClass.hIconSm = static_cast<HICON>(LoadImage(GetInst(), MAKEINTRESOURCE(IDI_ICON2),
		IMAGE_ICON, 16, 16, 0));
	RegisterClassEx(&wndClass);
}

//Deconstructors
WindowHandler::WindowClass::~WindowClass()
{
	UnregisterClass(CLASS_NAME, GetInst());
}

WindowHandler::~WindowHandler()
{
	DestroyWindow(hwnd);
}

void WindowHandler::ChangeWndTitle(const std::string& title)
{
	SetWindowText(hwnd, title.c_str());
}

//Getters
HINSTANCE WindowHandler::WindowClass::GetInst() noexcept
{
	return wndClass.hInst;
}

const char* WindowHandler::WindowClass::GetWindowName() noexcept
{
	return CLASS_NAME;
}


//User Window Setup
WindowHandler::WindowHandler(int w, int h, const char* wndName) : w(w), h(h)
{
	//Get window size
	RECT winBound;
	winBound.left = 100;
	winBound.right = w + winBound.left;
	winBound.top = 100;
	winBound.bottom = h + winBound.top;

	AdjustWindowRect(&winBound, WS_OVERLAPPEDWINDOW, FALSE);

	//Create window
	hwnd = CreateWindow(WindowClass::GetWindowName(), wndName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		winBound.right - winBound.left,
		winBound.bottom - winBound.top,
		nullptr, nullptr,
		WindowClass::GetInst(), this);

	ShowWindow(hwnd, SW_SHOWDEFAULT); //Show Window

	ptrGfx = std::make_unique<Graphics>(hwnd);//Creates gfx.obj

}

//Message Handlers
std::optional<int> WindowHandler::ProcessMessages()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{

		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}


		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return{};
}

Graphics& WindowHandler::Gfx()
{

	return *ptrGfx;
}

LRESULT CALLBACK WindowHandler::MsgSetup(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) noexcept
{
	if (msg == WM_NCCREATE) //Sends before WinAPI Init
	{
		//get ptr to the window handler
		const CREATESTRUCTW* const ptrCreate = reinterpret_cast<CREATESTRUCTW*>(l_param);
		WindowHandler* const ptrWnd = static_cast<WindowHandler*>(ptrCreate->lpCreateParams);

		//Store user data
		SetWindowLongPtr(hwnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(ptrWnd));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC,
			reinterpret_cast<LONG_PTR>(&WindowHandler::HandleMsgDispatch));

		return ptrWnd->MsgHandler(hwnd, msg, w_param, l_param);
	}

	return DefWindowProc(hwnd, msg, w_param, l_param); //If message is recieved before WM_NCCREATE, so returns default
}

LRESULT CALLBACK WindowHandler::HandleMsgDispatch(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) noexcept
{
	//getting ptr to window
	WindowHandler* const ptrWnd = reinterpret_cast<WindowHandler*>(
		GetWindowLongPtr(hwnd, GWLP_USERDATA));

	//Send Message to window handler
	return ptrWnd->MsgHandler(hwnd, msg, w_param, l_param);

}

LRESULT WindowHandler::MsgHandler(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KILLFOCUS:
	{
		kbd.ClearKeyStates();
	}
	break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN: //Allows for system keys (alt & F10)
	{
		if (!(l_param & 0x40000000 || kbd.CheckRepeatState()))
		{
			kbd.OnKeyDown(static_cast<unsigned char>(w_param));
		}
	}
	break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		kbd.OnKeyUp(static_cast<unsigned char>(w_param));
	}
	break;
	case WM_CHAR:
	{
		kbd.OnChar(static_cast<unsigned char>(w_param));
	}
	break;

	case WM_MOUSEMOVE:
	{
		const POINTS pt = MAKEPOINTS(l_param);
		if (pt.x >= 0 && pt.x < w && pt.y >= 0 && pt.y < h)
		{
			mouse.OnMoveMouse(pt.x, pt.y);

			if (!mouse.IsCursorInBound())
			{
				SetCapture(hwnd);
				mouse.MouseEnterBound();
			}
		}
		else
		{
			if (w_param & (MK_LBUTTON | MK_RBUTTON))
			{
				mouse.OnMoveMouse(pt.x, pt.y);
			}
			else
			{
				ReleaseCapture();
				mouse.MouseOutBound();
			}
		}
		break;
	}
	
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(l_param);
		mouse.LeftButtonDown(pt.x, pt.y);
	}
	break;
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(l_param);
		mouse.LeftButtonUp(pt.x, pt.y);
		if (pt.x < 0 || pt.x >= w || pt.y < 0 || pt.y >= h)
		{
			ReleaseCapture();
			mouse.MouseOutBound();
		}
	}
	break;
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(l_param);
		mouse.RightButtonDown(pt.x, pt.y);
	}
	break;
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(l_param);
		mouse.RightButtonUp(pt.x, pt.y);
		if (pt.x < 0 || pt.x >= w || pt.y < 0 || pt.y >= h)
		{
			ReleaseCapture();
			mouse.MouseOutBound();
		}
	}
	break;
	case WM_MOUSEWHEEL:
	{
		//const POINTS pt = MAKEPOINTS(l_param);
		int x = LOWORD(l_param);
		int y = HIWORD(l_param);
		const int r_d = GET_WHEEL_DELTA_WPARAM(w_param);
		mouse.MWheelRaw(x, y, r_d);

		if (r_d > 0)
		{
			mouse.MWheelUp(x, y);
		}
		else if ( r_d < 0)
		{
			mouse.MWheelDown(x, y);
		}
	}
	break;
	}


	return DefWindowProc(hwnd, msg, w_param, l_param);
}