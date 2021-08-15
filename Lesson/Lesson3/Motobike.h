#pragma once
#include "DynamicObject.h"

class Motobike :public DynamicObject {
public:
	Motobike();
	~Motobike();
	Motobike(int id, string name, Position position);

};