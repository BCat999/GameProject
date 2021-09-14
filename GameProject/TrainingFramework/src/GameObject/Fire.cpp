#include "Fire.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Application.h"

Fire::Fire(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, Skill sk)
	:Sprite2D(model,shader,texture),s(sk){
	Init();
}
Fire::~Fire() {
}

void Fire::Init()
{
	
	if (s == Skill::Fire) {
		m_time = 0;
		m_timeExist = 0.5f;
		SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("TextureShader"));
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Bullet.tga"));
		SetSize(25, 25);
		SetCamera(Application::GetInstance()->GetCamera());
		setDir(1);
		setSpeed(1000);
	}
	else if (s == Skill::Scratch) {
		m_time = 0;
		m_timeExist = 0.1f;
		SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("TextureShader"));
		SetTexture(ResourceManagers::GetInstance()->GetTexture("logo.tga"));
		SetSize(25, 25);
		SetCamera(Application::GetInstance()->GetCamera());
		setDir(1);
		setSpeed(1000);
	}
	
}
void Fire::Update(GLfloat deltaTime) {
	m_time += deltaTime;
	Move(deltaTime);
}

void Fire::Move(GLfloat deltaTime) {
	if(s==Skill::Fire)
		Set2DPosition(m_position.x + m_speed * deltaTime*m_fireDir, m_position.y);	
}
