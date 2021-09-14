#pragma once
#include "Sprite2D.h"
#include "GameStates/GameStateBase.h"
#include "ObjectPool.h"
#include "TileList.h"
//1605, 804

typedef struct Map
{
	int startX;
	int startY;
	int maxX;
	int maxY;
	int tile[MAX_MAP_Y][MAX_MAP_X];  // MAX_MAP_Y = 10, MAX_MAP_X = 400
	char* fileName;
} Map;

class GameMap : public Sprite2D
{
public:
	GameMap();
	~GameMap();
	void LoadMap(char* name);
	void Draw() override;
	void LoadMapTiles();
	Map GetMap() const { return map; }
	void SetMap(const Map& gMap) { map = gMap; }
private:
	Map map;
	std::list<std::shared_ptr<Sprite2D>>	sList;
};