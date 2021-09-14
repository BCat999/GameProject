#pragma once
#include "Sprite2D.h"
#include "Fox.h"

#include "../GameManager/ResourceManagers.h"

class Fox;
class Scratch :public Sprite2D {
public:
	Scratch():Sprite2D(),m_time(0),m_timeExist(5){}
	Scratch(Vector3 position);
	Scratch(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~Scratch();

	void Init() override;

	void Update(GLfloat deltaTime) ;
	bool IsExist() { return m_time < m_timeExist; };
	void Move(GLfloat deltaTime);

	int getDir() { return m_fireDir; };
	void	setDir(int dir) { m_fireDir = dir; };

private:
	float m_time;
	float m_timeExist;
	int m_fireDir;
};	