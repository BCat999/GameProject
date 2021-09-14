#include "GSMap1.h"

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

GSMap1::GSMap1()
{
}


GSMap1::~GSMap1()
{
}


void GSMap1::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG2.tga");
	
	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);

	// fox
	m_fox = std::make_shared<Fox>(model, shader, texture, 7, 0.07f);

	m_boss = std::make_shared<Enemy>(model, shader, texture, 6, 0.3f, Type::Boss);
	m_listEnemy.push_back(m_boss);

	sp = std::make_shared<Spirit>(model, shader, texture, 4, 0.1f, State::ALDULT);

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

	m_hpBoss = std::make_shared< Text>(shader, font, "Healt:" + std::to_string((int)m_boss->getHP()), TextColor::RED, 2.0);
	m_hpBoss->Set2DPosition(Vector2(Globals::screenWidth / 2, 100));
}

void GSMap1::Exit()
{
}


void GSMap1::Pause()
{
}

void GSMap1::Resume()
{
}


void GSMap1::HandleEvents()
{

}


void GSMap1::HandleKeyEvents(int key, bool bIsPressed)
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

void GSMap1::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMap1::HandleMouseMoveEvents(int x, int y)
{

}
void GSMap1::CreateEnermy(int t) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("healthGrass.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	std::shared_ptr<Enemy>	m_worn;
	while (t--) {
		int x = rand() % Globals::screenWidth + 100 - 100;
		if (x %9==0) {
			
			m_worn = std::make_shared<Enemy>(model, shader, texture, 7, 0.1f, Type::HealtGrass);
			m_worn->Set2DPosition(x, GROUND);
			
		}
		else {
			m_worn = std::make_shared<Enemy>(model, shader, texture, 4, 0.2f, Type::Worm);
			m_worn->Set2DPosition(x, GROUND);
			
		}
		m_listEnemy.push_back(m_worn);
	}
}
void GSMap1::Update(float deltaTime)
{
	if (keyPressed == 0) {
		m_fox->setCurrentFrames(0);
	}
	m_fox->UpdateTime(deltaTime);
	if (m_boss->getHP() > 0) {
		m_time += deltaTime;
		if (m_time >= m_timeSpawn) {
			CreateEnermy(4);
			m_time = 0;
		}
	}
	else {
		sp->Set2DPosition(Globals::screenWidth / 2, GROUND-50);
		sp->Move(Globals::screenWidth / 2,deltaTime);
		m_fox->setFireState(true);
	}
	

	for (auto it : m_listEnemy) {
		for (auto fire : m_listFire) {
			if(it->getHitFire(fire->GetPositionX(),fire->GetPositionY(),fire->getXWidth(),fire->getXHeight())){
				m_hpBoss->SetText("Healt:" + std::to_string((int)m_boss->getHP()));
				if (it->getHP() <= 0) {
					m_listRemoveEnemy.push_back(it);
				}
			}

		}
	}

	for (auto it : m_listRemoveEnemy) {
		m_listEnemy.remove(it);
	}
	m_listRemoveEnemy.clear();
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

	for (auto it : m_listEnemy) {
		it->UpdateTimeCountDown(deltaTime);
		it->Move(m_fox->GetPositionX(), deltaTime);
		for (int i = (it->GetPositionX() - it->getXWidth() / 2); i < (it->GetPositionX() + it->getXWidth() / 2); i++) {
			if ((i >= (foxPosition.x - m_fox->getXWidth() / 2)) && (i <= (foxPosition.x + m_fox->getXWidth() / 2))) {
				if (!it->countdown()&&(it->getCurrentFrames()==0)) {
					isAttack = true;
				}
			}
		}
	}
	for (auto it : m_listEnemy) {
		if (it->getType() == Type::HealtGrass) {
			if (m_boss->getHP() < BOSS_MAX_HP&&m_boss->getHP()>0) {
				it->UpdateTimeCountDown(deltaTime);
				if (!it->countdown()) {
					m_hpBoss->SetText("Healt:" + std::to_string((int)m_boss->getHP()));
					it->Health(m_boss);
					it->setShootTime(0);
				}
			}
				
		}
		if (isAttack == true) {
			it->Attack(foxPosition.x, deltaTime);
			if (it->getCurrentFrames() == (it->getNumFrames()-1)) {
				if (m_fox->getHit(it)) {
					m_score->SetText("Healt:" + std::to_string((int)m_fox->getHP()));
				}
				it->setShootTime(0);
				isAttack = false;
			}
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
		if (m_fox->getFireState() == true) {
			m_fox->Shoot(isRight, KEY_SHOT);
			m_listFire = m_fox->getFire();
		}
		
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
	if (keyPressed & KEY_SPACE) {
		if (m_fox->getSP(sp))
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MAP2);
	}
	if(m_fox->getHP()<=0)	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OVER);
}

void GSMap1::Draw()
{
	m_background->Draw();
	
	m_score->Draw();
	m_fox->Draw();
	m_hpBoss->Draw();
	sp->Draw();


	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listFire)
	{
		it->Draw();
	}
	for (auto it : m_listEnemy)
	{
		it->Draw();
	}
	
}