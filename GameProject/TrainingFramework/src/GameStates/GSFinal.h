#pragma once
#include "GameStateBase.h"
#include "Fire.h"
#include "GSPlay.h"
class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class AnimationSprite;
class Fox;
class Enemy;
class Scratch;
class Spirit;
class GSFinal :
	public GameStateBase
{
public:
	GSFinal();
	~GSFinal();

	void	Init() override;
	void	Exit() override;
	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	void	CreateEnermy(int t);
protected:
	
	bool isFalling = false;
	bool isJumping = false;
	bool isRight = true;
	bool isScratch = false;
	int speed = 0;
	int keyPressed = 0;
	int worm = 4;
	bool isAttack = false;
	float m_time = 0;
	float m_timeSpawn = 10;


	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score; 
	std::shared_ptr<Text>		m_hpBoss;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Fox>	m_fox;
	std::list<std::shared_ptr<Fire>> m_listFire;
	std::list<std::shared_ptr<Fire>> m_listRemoveFire;

	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	std::list<std::shared_ptr<Enemy>> m_listRemoveEnemy;


	std::shared_ptr<Spirit>	sp;
};

