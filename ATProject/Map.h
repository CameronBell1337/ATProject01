#pragma once
#include "Grnd.h"
#include "Waypoint.h"

class Map
{
public:
	Map(Graphics& graphics);
	Map(const Map&) = delete;
	Map& operator=(const Map&) = delete;

	
	 

	void DrawObj(Graphics& graphics);
	void SetPos(Vector3 pos) noexcept;
	void SetColour(DirectX::XMFLOAT3 colour);

	Grnd* GetGrnd(Vector3 pos);
	Grnd* GetGrndCoord(int x, int y);
	Grnd* GetTileType(Vector3 pos);

	Waypoint* GetNextWP();

	static const int mapW = 41;
	static const int mapH = 24;

	std::vector<std::vector<Grnd>> grnd;

private:
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };

	DirectX::XMFLOAT3 mainColours;
	DirectX::XMFLOAT3 colours0= { 0.0f,0.64f,0.0f };
	DirectX::XMFLOAT3 colours1 = { 0.95f,0.64f,0.37f };
	DirectX::XMFLOAT3 colours2 = { 0.37f,0.69f,0.95f };
	DirectX::XMFLOAT3 colours3 = { 1.0f,1.0f,1.0f };

	//waypoints
	Vector3 wayPoint0 = Vector3(3, 11, 1);
	Vector3 wayPoint1 = Vector3(9, 11, 1);
	Vector3 wayPoint2 = Vector3(9, 19, 1);
	Vector3 wayPoint3 = Vector3(15, 19, 1);
	Vector3 wayPoint4 = Vector3(15, 11, 1);
	Vector3 wayPoint5 = Vector3(19, 11, 1);
	Vector3 wayPoint6 = Vector3(19, 5, 1);
	Vector3 wayPoint7 = Vector3(23, 5, 1);
	Vector3 wayPoint8 = Vector3(23, 8, 1);
	Vector3 wayPoint9 = Vector3(26, 8, 1);
	Vector3 wayPoint10 = Vector3(26, 11, 1);
	Vector3 wayPoint11 = Vector3(30, 11, 1);
	Vector3 wayPoint12 = Vector3(30, 5, 1);
	Vector3 wayPoint13 = Vector3(42, 5, 1);

	std::vector<Waypoint> wp;

};
