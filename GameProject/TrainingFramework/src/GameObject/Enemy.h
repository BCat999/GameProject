#pragma once 
#include "AnimationSprite.h"
#include "Fire.h"
enum class Type {
	Worm = 0,
	Boss,
	HealtGrass,
};
class Enemy : public AnimationSprite
{
public:
	
	Enemy() : AnimationSprite(), m_hp(5), m_speed(0){}
	Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrames,
		float frameTime,Type type);
	~Enemy();


	void	setHP(int hp);
	void	setSpeed(float speed);
	void	Init() override;
	void	Move(float x, float deltatime);
	void	Attack(float x, float deltatime);
	void	Health(std::shared_ptr<Enemy>	enemy);
	int		getHP();
	float	getSpeed();
	Type	getType() { return m_type; };
	void	UpdateTimeCountDown(GLfloat deltaTime);
	bool	getHitFire(int x, int y, int w, int h);
	bool	countdown() { return m_shootTime < m_shootInterval; };
	void	setShootTime(float t) { m_shootTime = t; }

private:

	int	m_hp;
	float m_speed;
	Type m_type;
	float m_shootInterval;
	float m_shootTime;
};

