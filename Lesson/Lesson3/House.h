#pragma once
#include "StaticObject.h"

class House :public StaticObject {
public:
	House();
	~House();
	House(int id, string name, Position position);
};