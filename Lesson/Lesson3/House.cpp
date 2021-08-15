#include "House.h"

House::House(){}

House::~House(){}

House::House(int id, string name, Position p) : StaticObject(id, name, p) {}
