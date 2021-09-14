#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "AnimationSprite.h"
#include "Fox.h"
#include "Enemy.h"
#include "Application.h"
#include "Spirit.h"
GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play_main.tga");
	
	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);

	// fox
	m_fox = std::make_shared<Fox>(model, shader, texture, 7, 0.07f);

	sp = std::make_shared<Spirit>(model, shader, texture, 6, 0.5f, State::SPIRIT);
	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Comici.ttf");
	m_score = std::make_shared< Text>(shader, font, "Healt:" + std::to_string((int)m_fox->getHP()), TextColor::WHITE, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{

}


void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed == true) {
		switch (key) {
		case VK_LEFT:
			keyPressed |= KEY_MOVE_LEFT;
			break;
		case VK_RIGHT:
			keyPressed |= KEY_MOVE_RIGHT;
			break;
		case VK_UP:
			keyPressed |= KEY_UP;
			break;
		case ' ':
			keyPressed |= KEY_SPACE;
			break;
		case 'Z':
			keyPressed |= KEY_SHOT;
			break;
		case 'X':
			keyPressed |= KEY_SCRATCH;
			break;
		}
	}
	else {
	switch (key) {
	case VK_LEFT:
		keyPressed ^= KEY_MOVE_LEFT;
		break;
	case VK_RIGHT:
		keyPressed ^= KEY_MOVE_RIGHT;
		break;
	case VK_UP:
		keyPressed ^= KEY_UP;
		break;
	case ' ':
		keyPressed ^= KEY_SPACE;
		break;
	case 'Z':
		keyPressed ^= KEY_SHOT;
		break;
	case 'X':
		keyPressed ^= KEY_SCRATCH;
		break;
	}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{

}
void GSPlay::CreateEnermy(int t) {

}
void GSPlay::Update(float deltaTime)
{
	
	sp->Update(deltaTime);
	m_fox->UpdateTime(deltaTime);
	//foxMove
	if (keyPressed & KEY_MOVE_LEFT && (m_fox->GetPositionX() > 0)) {
		m_fox->Move(deltaTime, KEY_MOVE_LEFT);
		isRight = false;
	}
	if (keyPressed & KEY_MOVE_RIGHT && (m_fox->GetPositionX() < Globals::screenWidth)) {
		m_fox->Move(deltaTime, KEY_MOVE_RIGHT);
		isRight = true;
	}
	Vector3 foxPosition = m_fox->GetPosition();

	if (isJumping == true) {
		if (speed > -6000 && isFalling == false) {
			speed -= GRAVITY_SPEED;
			isFalling = true;
			m_fox->setCurrentFrames(4);
		}
		if (isFalling == true) {
			speed += GRAVITY_SPEED * 2;
			if (foxPosition.y >= GROUND-10) {
				speed = 0;
				isJumping = false;
				foxPosition.y = GROUND-10;
				m_fox->setCurrentFrames(0);
			}
		}
	}

	if (keyPressed & KEY_UP) {
		if (isJumping == false) {
			speed = -1000;
			isJumping = true;
			isFalling = false;
		}
	}
	foxPosition.y += speed * deltaTime;
	m_fox->Set2DPosition(foxPosition.x, foxPosition.y);

	//FoxSkill
	if (keyPressed & KEY_SCRATCH) {
		isScratch = true;
	}
	if (keyPressed & KEY_SPACE) {
		if(m_fox->getSP(sp))
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MAP1);
	}
	if (isScratch) {
		m_fox->Shoot(isRight, KEY_SCRATCH);
		isScratch = false;
		m_listFire = m_fox->getFire();
	}
	for (auto it : m_listFire)
	{
		it->Update(deltaTime);
		if (!it->IsExist()) {
			m_listRemoveFire.push_back(it);
		}
	}
	for (auto it : m_listRemoveFire)
	{
		m_listFire.remove(it);
	}
	m_listRemoveFire.clear();

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if (keyPressed == false) {
		m_fox->setCurrentFrames(0);
	}
	if(m_fox->getHP()<=0)	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OVER);
}

void GSPlay::Draw()
{
	m_background->Draw();
	
	m_score->Draw();
	m_fox->Draw();
	sp->Draw();
	for (auto it : m_listFire)
	{
		it->Draw();
	}

	for (auto it : m_listButton)
	{
		it->Draw();
	}
}