#include "GSFinal.h"

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
GSFinal::GSFinal()
{
}


GSFinal::~GSFinal()
{
}


void GSFinal::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_Final.tga");
	
	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);

	// fox
	m_fox = std::make_shared<Fox>(model, shader, texture, 7, 0.07f);

	sp = std::make_shared<Spirit>(model, shader, texture, 4, 0.5f, State::BOSS);
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

	m_hpBoss = std::make_shared< Text>(shader, font, "Healt:" + std::to_string((int)sp->getHP()), TextColor::RED, 2.0);
	m_hpBoss->Set2DPosition(Vector2(Globals::screenWidth / 2, 100));
}

void GSFinal::Exit()
{
}


void GSFinal::Pause()
{
}

void GSFinal::Resume()
{
}


void GSFinal::HandleEvents()
{

}


void GSFinal::HandleKeyEvents(int key, bool bIsPressed)
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

void GSFinal::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSFinal::HandleMouseMoveEvents(int x, int y)
{

}
void GSFinal::CreateEnermy(int t) {

}
void GSFinal::Update(float deltaTime)
{
	
	for (auto fire : m_listFire) {
		if (sp->getHitFire(fire->GetPositionX(), fire->GetPositionY(), fire->getXWidth(), fire->getXHeight())) {
			m_hpBoss->SetText("Healt:" + std::to_string((int)sp->getHP()));
		}

	}
	
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
	sp->Move(foxPosition.x, deltaTime);
	if (isAttack == false) {
		sp->UpdateTimeCountDown(deltaTime);
	}
	std::cout << isAttack;
	for (int i = (sp->GetPositionX() - sp->getXWidth() / 2); i < (sp->GetPositionX() + sp->getXWidth() / 2); i++) {
		if ((i >= (foxPosition.x - m_fox->getXWidth() / 2)) && (i <= (foxPosition.x + m_fox->getXWidth() / 2))) {
			if (!sp->countdown() && (sp->getCurrentFrames() == 0)) {
				isAttack = true;
				
			}
		}
	}
	if (isAttack == true) {
		sp->Attack(foxPosition.x, deltaTime);
		if (sp->getCurrentFrames() == (sp->getNumFrames() - 1)) {
			if (m_fox->getSP(sp)) {
				m_score->SetText("Healt:" + std::to_string((int)m_fox->getHP()));
				sp->setShootTime(0);
				isAttack = false;
			}
			sp->setShootTime(0);
			isAttack = false;
		}
	}
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
	if (isScratch) {
		m_fox->Shoot(isRight, KEY_SCRATCH);
		isScratch = false;
		m_listFire = m_fox->getFire();
	}
	if (keyPressed & KEY_SHOT) {
			m_fox->Shoot(isRight, KEY_SHOT);
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
	if(sp->getHP()<=0)	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_WIN);
}

void GSFinal::Draw()
{
	m_background->Draw();
	
	m_score->Draw();
	m_fox->Draw();
	sp->Draw();
	m_hpBoss->Draw();
	for (auto it : m_listFire)
	{
		it->Draw();
	}

	for (auto it : m_listButton)
	{
		it->Draw();
	}
}