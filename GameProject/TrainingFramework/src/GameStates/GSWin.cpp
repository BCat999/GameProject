#include "GSWin.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"

GSWin::GSWin()
{
}


GSWin::~GSWin()
{
}


void GSWin::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play2_2.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button clode
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Comici.ttf");
	m_score = std::make_shared< Text>(shader, font, "Victory", TextColor::BLACK, 4.0);
	m_score->Set2DPosition(Vector2(Globals::screenWidth / 2-100, Globals::screenHeight / 2));
}

void GSWin::Exit()
{
}


void GSWin::Pause()
{
}

void GSWin::Resume()
{
}


void GSWin::HandleEvents()
{
}

void GSWin::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSWin::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSWin::HandleMouseMoveEvents(int x, int y)
{
}

void GSWin::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSWin::Draw()
{
	m_score->Draw();
	//m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}