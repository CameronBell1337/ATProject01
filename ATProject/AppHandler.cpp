#include "AppHandler.h"
#include <sstream>
#include <iterator>
#include <memory>
#include <algorithm>

#include "Box.h"
#include "Loon.h"
#include "Floor.h"
#include "MathC.h"
#include "GrndSelector.h"
#include "Map.h"
#include "Objects.h"
#include "Ballon.h"


App::App() : window(1280, 720, "A GAME!")
{
	//Old Test code
	/*class Init
	{
	public:
		Init(Graphics& _graphics)
			:
			graphics(_graphics)
		{}

		std::unique_ptr<Draw> operator()()
		{
			switch (caseSize(rng))
			{
			case 0:
				return {};
			case 1:
				return {};
			case 2:
				return std::make_unique <Floor> (graphics, rng, adist, ddist, odist, rdist,
					sliceDiv, stackDiv);
			default:
				return{};

			}
		}
	private:
		Graphics& graphics;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f, _pi * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f, _pi * 2.0f };
		std::uniform_real_distribution<float> odist{ 0.0f, _pi * 0.3f };
		std::uniform_real_distribution<float> rdist{ 0.5f, 20.0f };
		std::uniform_real_distribution<float> bdist{ 0.5f, 3.0f };
		std::uniform_int_distribution<int> sliceDiv{ 5,20 };
		std::uniform_int_distribution<int> stackDiv{ 10,40 };
		std::uniform_int_distribution<int> caseSize{ 1,2 };
	};
	
	Init _i(window.Gfx());
	drawables.reserve(drawAmount);
	std::generate_n(std::back_inserter(drawables), drawAmount, _i);*/
	//setting camera and projection Matrix
	window.Gfx().SetProjectionM(
		DirectX::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 400.0f));
	window.Gfx().SetCamera(DirectX::XMMatrixTranslation(0.0f, 0.0f, -20.f));


	//Initialisation
	
	data.objs = &objs;
	data.graphics = &window.Gfx();
	data.kbd = &window.kbd;
	map = new Map(window.Gfx());
	data.map = map;
	data.points = startingPoints;
	data.isDestroyed = false;
	data.currentMulti = 1.0f;

	Objects* init = new GrndSelector(window.Gfx());
	objs.emplace_back(init);

}


App::~App()
{
	for (auto& gObjs : objs)
	{
		if (gObjs)
		{
			//TODO Fix heap error exception
			delete[] gObjs;
			gObjs = nullptr;
		}
	}
	objs.clear();

	if (map)
	{
		delete map;
		map = nullptr;
	}

}

int App::Start()
{
	while (true)
	{
		if (const auto e_code = WindowHandler::ProcessMessages())
		{
			return *e_code;
		}
		Update();
	}

	BOOL result;
	MSG msg;
	if (result == -1)
	{
		return -1;
	}
	return msg.wParam;

}

void App::Update()
{
	window.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	window.Gfx().SetCamera(mainCam.GetMatrix());
	float deltaT = timer.ElapseTime();
	data.dT = deltaT;
	data.isDestroyed = false;
	const auto k_input = window.kbd.GetKeyInput();
	const auto m_input = window.mouse.GetMouseInput();
	
	for (auto& init : objs)
	{
		init->Update(&data);
	}


	

	// #### Mouse Input #### ///
	if (m_input.GetEventType() == Mouse::Input::EventType::m_wheel_up)
	{
		mainCam.UpdateCam({ 0.0f,0.0f,deltaT * 2});
		std::ostringstream oss;
		oss << "("<<  m_input.GetMWheelRaw() << ")/n";
		//window.ChangeWndTitle(oss.str());
		
		
	}
	if (m_input.GetEventType() == Mouse::Input::EventType::m_wheel_down)
	{
		mainCam.UpdateCam({ 0.0f,0.0f,-deltaT * 2});
		std::ostringstream oss;
		oss << "(" << m_input.GetMWheelRaw() << ")/n";
		//window.ChangeWndTitle(oss.str());
	}
	// #### Mouse Input #### ///

	// #### Keyboard Input #### ///
	if (window.kbd.IsKeyPressed('A'))
	{
		mainCam.UpdateCam({ -deltaT,0.0f,0.0f });
		std::ostringstream oss;
		oss << "(" << k_input.GetKeyCode() << ")/n";
		//window.ChangeWndTitle(oss.str());
	}
	if (window.kbd.IsKeyPressed('D'))
	{
		mainCam.UpdateCam({ deltaT,0.0f,0.0f});
		std::ostringstream oss;
		oss << "(" << k_input.GetKeyCode() << ")/n";
		//window.ChangeWndTitle(oss.str());
	}
	if (window.kbd.IsKeyPressed('W'))
	{
		mainCam.UpdateCam({ 0.0f,deltaT,0.0f });
		std::ostringstream oss;
		oss << "(" << k_input.GetKeyCode() << ")/n";
		//window.ChangeWndTitle(oss.str());
	}
	if (window.kbd.IsKeyPressed('S'))
	{
		mainCam.UpdateCam({ 0.0f,-deltaT,0.0f });
		std::ostringstream oss;
		oss << "(" << k_input.GetKeyCode() << ")/n";
		//window.ChangeWndTitle(oss.str());
	}

	if (window.kbd.IsKeyPressed('R'))
	{
		mainCam.ResetCam();
		std::ostringstream oss;
		oss << "(" << k_input.GetKeyCode() << ")/n";
		//window.ChangeWndTitle(oss.str());
	}
	
	// #### Keyboard Input #### ///

	const auto delta = window.mouse.ReadRawDelta();
	mainCam.Rotate(delta.x, delta.y);

	std::vector<Objects*>& dList = Objects::GetObjDstryList();
	while (dList.size())
	{
		Objects* ptr = dList.back();
		
		dList.pop_back();

		for (std::vector<Objects*>::iterator it = objs.begin(); it != objs.end(); it++)
		{
		
			if ((*it) == ptr)
			{
				delete (*it);
				(*it) = nullptr;

				
				if (data.currentMulti != 1.0f)
				{
					data.points += (10.0f * data.currentMulti);
					data.currentMulti = 1.0f;
				}
				
				objs.erase(it);
				break;
			}
		}
	}
	//Creates list to store added towers at runtime
	std::vector<Objects*>& cList = Objects::GetObjList();
	while (cList.size())
	{
		Objects* ptr = cList.back();
		cList.pop_back();
		objs.emplace_back(ptr);
	}
	window.kbd.endFrame();
	
	map->DrawObj(window.Gfx());
	
	for (auto& init : objs)
	{
		//init->Update(&data);
		init->DrawObj(&window.Gfx());
	}
	
	
	window.Gfx().EndFrame();
}

