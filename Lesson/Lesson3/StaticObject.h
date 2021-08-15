#pragma once
#include "BasicObject.h"

class StaticObject :public BaseObject {
public:
	StaticObject();
	~StaticObject();
	StaticObject(int id, string name, Position Position);

	void move(Position p);
	void move(int x, int y);
};
