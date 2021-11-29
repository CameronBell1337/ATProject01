#pragma once
#include "WindowHandler.h"
#include "Timer.h"
#include "Camera.h"
#include "Map.h"
#include "Data.h"
#include "Grnd.h"
#include "Waypoint.h"
#include "Ballon.h"

class App
{
public:
	App();
	~App();

	int Start();

private:

	void Update();

	WindowHandler window;
	Timer timer;

	Camera mainCam;
	Data data;
	Map* map;

	Ballon* loon;

	std::vector<std::unique_ptr<class Draw>> drawables;
	std::vector<Waypoint> wps;

	
	
	float startingPoints = 500;

	std::vector<class Objects*> objs;
	static constexpr size_t drawAmount = 80;
};