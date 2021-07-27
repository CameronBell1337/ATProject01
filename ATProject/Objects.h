#pragma once
#include <vector>
#include "Vector3.h"
#include "Box.h"
#include "Data.h"


class Objects
{
public:
	Objects() = default;
	~Objects();

	Objects(const Objects&) = delete;
	Objects& operator=(const Objects&) = delete;
	virtual void Update(Data* data) = 0;
	virtual void DrawObj(Graphics* graphics);

	void SetPos(Vector3 _pos);
	void SetScale(Vector3 _scale);

	Vector3 GetPos();
	Vector3 GetScale();

	static void DestroyObj(Objects* obj);
	static void CreateObj(Objects* obj);

	static std::vector<Objects*>& GetObjDstryList()
	{
		return objToDestroy;
	};

	static std::vector<Objects*>& GetObjList()
	{
		return createObjList;
	};

	Draw* m;

private:

	static std::vector<Objects*> objToDestroy;
	static std::vector<Objects*> createObjList;

	Vector3 pos;
	Vector3 scale;
};
