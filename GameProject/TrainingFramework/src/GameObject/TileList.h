#pragma once
#include "Sprite2D.h"

#ifndef TILELIST_H
#define TILELIST_H

class TileList : public Sprite2D{
public:
	
	void Init();
	~TileList();

	std::list<std::shared_ptr<Sprite2D>>	sList;
private:
	TileList();
};
#endif // TILELIST_H

