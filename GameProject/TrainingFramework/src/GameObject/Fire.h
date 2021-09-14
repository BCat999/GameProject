#pragma once
#include "Sprite2D.h"
#include "Fox.h"
#include "Fire.h"
#include "../GameManager/ResourceManagers.h"
enum class Skill {
	Fire=4,
	Scratch
};
class Fox;
class Fire :public Sprite2D {
public:
	Fire():Sprite2D(),m_time(0),m_timeExist(5),m_speed(500){}
	Fire(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, Skill sk);
	~Fire();

	void Init() override;

	void Update(GLfloat deltaTime) ;
	void setSpeed(int sp) { m_speed = sp; };
	bool IsExist() { return m_time < m_timeExist; };
	void Move(GLfloat deltaTime);
	Skill	getType() { return s; };
	int		 getDir() { return m_fireDir; };
	void	setDir(int dir) { m_fireDir = dir; };

private:
	int m_speed;

	float m_time;
	float m_timeExist;
	int m_fireDir;
	
	Skill s;
};	