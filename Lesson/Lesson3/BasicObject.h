#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Position {
public:
	int x;
	int y;
	Position() {
		this->x = 0;
		this->y = 0;
	}

	~Position() {}

	Position(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void move(int x, int y) {
		this->x += x;
		this->y += y;
	}
};
class BaseObject {
private:
	int id;
	string name;
	Position position;
public:
	BaseObject();
	~BaseObject();
	BaseObject(int id, string name, Position position);

	int getid();
	void setid();

	string getName();
	void setName();

	Position getPosition();
	void setPosition(Position p);

	virtual void move(Position p);
	virtual void move(int x, int y);

	void printPosition();
};
