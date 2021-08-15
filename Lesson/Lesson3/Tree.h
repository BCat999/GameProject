#pragma once
#include "StaticObject.h"

class Tree : public StaticObject
{
public:
	Tree();
	~Tree();
	Tree(int id, string name, Position p);
};

