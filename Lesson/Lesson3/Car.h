#pragma once
#include "DynamicObject.h"

class Car :public DynamicObject {
public:
	Car();
	~Car();
	Car(int id, string name, Position position);

};