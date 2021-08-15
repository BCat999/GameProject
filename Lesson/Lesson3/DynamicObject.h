#pragma once
#include "BasicObject.h";

class DynamicObject : public BaseObject
{

public:
	DynamicObject();
	~DynamicObject();
	DynamicObject(int id, string name, Position pos);

	void move();

};
