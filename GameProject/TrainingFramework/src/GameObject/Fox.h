#pragma once 

#include "AnimationSprite.h"
#include "Fire.h"
#include "Enemy.h"
#include "Spirit.h"
class Spirit;
class Enemy;
class Fire;
class Fox : public AnimationSprite
{
public:
	Fox() : AnimationSprite(), m_hp(5), m_Fire(false), m_HeadButt(false), m_shootInterval(1), m_shootTime(0){}
	Fox(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrames,float frameTime);
	~Fox();

	void	Init();
	void	setHP(int hp);
	void	Move(GLfloat deltaTime,int key);
	int		getHP() { return m_hp; };
	void	UpdateTime(GLfloat deltaTime);
	void	Shoot(bool dic,int key);
	bool	countdown() { return m_shootTime < m_shootInterval; };
	bool	getHit(std::shared_ptr<Enemy>	enemy);

	bool	getSP(std::shared_ptr<Spirit>	sp);
	void	setFireState(bool x) { m_Fire = x; };
	bool	getFireState() { return m_Fire; };

	std::list<std::shared_ptr<Fire>> m_listFire;
	std::list<std::shared_ptr<Fire>> getFire();

private:
	
	int	m_hp;
	bool m_Fire;
	bool m_HeadButt;
	
	float m_shootInterval;
	float m_shootTime;
};

