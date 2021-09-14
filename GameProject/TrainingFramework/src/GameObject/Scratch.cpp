#include "Scratch.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Application.h"

Scratch::Scratch(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	:Sprite2D(model,shader,texture){
	Init();
}
Scratch::~Scratch() {
}
Scratch::Scratch(Vector3 position)
{
	Set2DPosition(Vector2(position.x, position.y));
	Init();
}

void Scratch::Init()
{
	m_time = 0;
	m_timeExist = 0.5f;
	SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
	SetShaders(ResourceManagers::GetInstance()->GetShader("TextureShader"));
	SetTexture(ResourceManagers::GetInstance()->GetTexture("logo.tga"));
	SetSize(80, 80);
	SetCamera(Application::GetInstance()->GetCamera());
	setDir(1);
}
void Scratch::Update(GLfloat deltaTime) {
	m_time += deltaTime;
	Move(deltaTime);
}

void Scratch::Move(GLfloat deltaTime) {

	Set2DPosition(m_position.x, m_position.y);
	
}

