#include "TileList.h"
#include "Texture.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Application.h"
#include "../GameManager/ResourceManagers.h"


typedef struct Map {
	int startX;
	int startY;

	int maxX;
	int maxY;

	int 
};
TileList::TileList() {

}
void TileList::Init() {
		std::shared_ptr<Sprite2D>	s;
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Ground.tga"));
		sList.push_back(s);
}
TileList::~TileList() {

}