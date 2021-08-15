#include "BasicObject.h"

BaseObject::BaseObject() {
	this->id = 0;
	this->name = "";
	this->position.x = 0;
	this->position.y = 0;
}

BaseObject::~BaseObject() {}

BaseObject::BaseObject(int id, string name, Position p) {
	this->id = id;
	this->name = name;
	this->position = p;
}

int BaseObject::getid() {
	return this->id;
}
void BaseObject::setid() {
	this->id = id;
}

string BaseObject::getName() {
	return this->name;
}
void BaseObject::setName() {
	this->name = name;
}

Position BaseObject::getPosition() {
	return this->position;
}
void BaseObject::setPosition(Position p) {
	this->position.x = p.x;
	this->position.y = p.y;
}

void BaseObject::move(Position p) {
	this->position = p;
}
void BaseObject::move(int x, int y) {
	this->position.move(x, y);
}
void BaseObject::printPosition() {
	cout << getName() << "(" << this->position.x << ", " << this->position.y << ")" << endl;
}



