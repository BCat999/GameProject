#pragma once 
#include "AnimationSprite.h"
#include "Fire.h"
enum class State {
	SPIRIT = 8,
	ALDULT,
	BOSS,
};
class Spirit : public AnimationSprite
{
public:

	Spirit() : AnimationSprite(), m_hp(0), m_speed(0) {}
	Spirit(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrames,
		float frameTime, State type);
	~Spirit();


	void	setHP(int hp);
	void	setSpeed(float speed);
	void	Init() override;
	void	Move(float x, float deltatime);
	void	Attack(float x, float deltatime);
	int		getHP();
	float	getSpeed();
	State	getType() { return m_type; };
	void	UpdateTimeCountDown(GLfloat deltaTime);
	bool	getHitFire(int x, int y, int w, int h);
	bool	countdown() { return m_shootTime < m_shootInterval; };
	void	setShootTime(float t) { m_shootTime = t; }
	void	setType(State t) { m_type = t; };
private:

	int	m_hp;
	float m_speed;
	State m_type;
	float m_shootInterval;
	float m_shootTime;
};

