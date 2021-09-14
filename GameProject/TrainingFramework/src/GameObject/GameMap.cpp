#include "GameMap.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "GameButton.h"
#include "AnimationSprite.h"
#include "Fox.h"
#include "Enermy.h"
#include "Ground.h"
#include "Application.h"
#include "../GameManager/ResourceManagers.h"


void GameMap::LoadMap(char* name) {
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) {
		return;
	}
	map.maxX = 0;
	map.maxY = 0;
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			fscanf_s(fp, "%d", &map.tile[i][j]);
			int val = map.tile[i][j];
			if (val > 0) {
				if (j > map.maxX) {
					map.maxX = j;
				}
				if (i > map.maxY) {
					map.maxY = i;
				}
			}
		}
	}

	map.maxX = (map.maxX + 1) * TILE_SIZE;
	map.maxY = (map.maxY + 1) * TILE_SIZE;

	map.startX = 0;
	map.startY = 0;

	map.fileName = name;
	fclose(fp);
}

void GameMap::LoadMapTiles() {
	for (int i = 0; i < MAX_TILES; i++) {
		std::shared_ptr<Sprite2D>	s;
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Ground.tga"));
		SetSize(64, 64);
		Set2DPosition(i, j);
		sList.push_back(s);
	}
}
