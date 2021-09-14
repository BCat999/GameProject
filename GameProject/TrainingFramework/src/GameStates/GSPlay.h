#pragma once
#include "GameStateBase.h"
#include "Fire.h"
class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class AnimationSprite;
class Fox;
class Enemy;
class Scratch;
class Spirit;
class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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

protected:
	
	bool isFalling = false;
	bool isJumping = false;
	bool isRight = true;
	bool isScratch = false;
	int speed = 0;
	int keyPressed = 0;



	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score; 

	std::list<std::shared_ptr<GameButton>>	m_listButton;

	std::shared_ptr<Fox>	m_fox;
	std::list<std::shared_ptr<Fire>> m_listFire;
	std::list<std::shared_ptr<Fire>> m_listRemoveFire;

	std::shared_ptr<Spirit>	sp;
};

