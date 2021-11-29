#include "Objects.h"


void Objects::DrawObj(Graphics* graphics)
{
	if (m != nullptr)
	{
		m->DrawObj(*graphics);
	}
}

Objects::~Objects()
{
	
	delete[] m;
	m = nullptr;
	
}

void Objects::SetPos(Vector3 _pos)
{
	pos = _pos;
	m->SetPos(_pos);
}

void Objects::SetScale(Vector3 _scale)
{
	this->scale =  _scale;
	m->SetScale(_scale);
}

Vector3 Objects::GetPos()
{
	return pos;
}

Vector3 Objects::GetScale()
{
	return scale;
}


//Creates a list of objects to be deleted once finished with
std::vector<Objects*> Objects::objToDestroy = std::vector<Objects*>();
void Objects::DestroyObj(Objects* obj)
{
	if (!std::count(objToDestroy.begin(), objToDestroy.end(), obj))
	{
		objToDestroy.emplace_back(obj);
	}
}

//Creates vector list to store all run time made objects
std::vector<Objects*> Objects::createObjList = std::vector<Objects*>();
void Objects::CreateObj(Objects* obj)
{
	if (!std::count(createObjList.begin(), createObjList.end(), obj))
	{
		createObjList.emplace_back(obj);
	}
}