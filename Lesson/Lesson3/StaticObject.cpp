#include "StaticObject.h"

StaticObject::StaticObject(){}

StaticObject::~StaticObject(){}

StaticObject::StaticObject(int id, string name, Position p) : BaseObject(id,name,p){}

void StaticObject::move(Position p) {
	cout << getName() << " Can't move" << endl;
}
void StaticObject::move(int x, int y) {
	cout << getName() << " Can't move" << endl;
}