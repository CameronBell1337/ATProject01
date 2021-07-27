#pragma once

struct Data
{
	class Graphics* graphics;
	class Map* map;
	class Keyboard* kbd;
	std::vector<class Objects*>* objs;
	float dT;
	float points;

	bool isDestroyed;
	
};