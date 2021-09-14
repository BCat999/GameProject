#include "GSGameOver.h"

GSGameOver::GSGameOver() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSGameOver::~GSGameOver()
{
}


void GSGameOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("logo.tga");

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Comici.ttf");
	m_score = std::make_shared< Text>(shader, font, "Game Over", TextColor::BLACK, 2.0);
	m_score->Set2DPosition(Vector2(Globals::screenWidth / 2-100, Globals::screenHeight / 2));
}

void GSGameOver::Exit()
{
}


void GSGameOver::Pause()
{
}

void GSGameOver::Resume()
{
}


void GSGameOver::HandleEvents()
{
}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSGameOver::HandleMouseMoveEvents(int x, int y)
{
}

void GSGameOver::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 5)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSGameOver::Draw()
{
	m_score->Draw();
}
