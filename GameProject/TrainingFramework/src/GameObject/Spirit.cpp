#include "Spirit.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"
#include "../GameManager/ResourceManagers.h"

Spirit::Spirit(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrames,
	float frameTime, State type) : AnimationSprite(model, shader, texture, numFrames, frameTime), m_type(type) {
	Init();
}
Spirit :: ~Spirit() {

}
void Spirit::Init() {
	if (m_type == State::SPIRIT) {
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Spirit.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		Set2DPosition(Globals::screenWidth / 2 + 50, GROUND - 50);
		setSpeed(1);
		setNumFrames(4);
		setHP(10);
		SetSize(100,100);
	}
	else if (m_type == State::ALDULT) {
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Spirit.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		Set2DPosition(Globals::screenWidth / 2 , -500);
		setNumFrames(4);
		setSpeed(0.01);
		setHP(0);
		SetSize(180, 180);
	}
	else if (m_type == State::BOSS) {
		m_shootInterval = 4.0f;
		m_shootTime = 0.0f;
		
		Set2DPosition(Globals::screenWidth / 2 + 50, GROUND - 100);
		SetTexture(ResourceManagers::GetInstance()->GetTexture("SPBoss.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		setNumFrames(4);
		setSpeed(2);
		setHP(500);
		SetSize(300, 300);
	}

}

void Spirit::Move(float x, float deltatime) {

	if (m_type == State::ALDULT) {
		Update(deltatime);
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Spirit.tga"));
		if (m_position.x<=x-200) {
			m_position.x += m_speed;
		}else if(m_position.x >= x - 200){
			m_position.x -= m_speed * deltatime;
		}
		Set2DPosition(m_position.x, m_position.y);

	}
	else if (m_type == State::BOSS) {
		setSpeed(2);
		SetTexture(ResourceManagers::GetInstance()->GetTexture("SPBoss.tga"));
		if (x >= m_position.x) {
			m_position.x += m_speed-1;
		}
		else {

			m_position.x -= m_speed * deltatime;
		}
		Set2DPosition(m_position.x, m_position.y);
		Update(deltatime);

	}
	else {
		Update(deltatime);
	}

}


void Spirit::UpdateTimeCountDown(GLfloat deltaTime) {
	m_shootTime += deltaTime;

}
void Spirit::Attack(float x, float deltatime) {
	if (m_type == State::BOSS) {
		setSpeed(0);
			SetTexture(ResourceManagers::GetInstance()->GetTexture("Spatt.tga"));
		Update(deltatime);
	}
}

bool Spirit::getHitFire(int x, int y, int w, int h) {
	for (int i = x - w / 2; i < x + w / 2; i++) {
		if ((i >= m_position.x - 10) && (i <= m_position.x + 10) && (y < m_position.y + m_iHeight) && (y > m_position.y - m_iHeight)) {
			m_hp -= FOX_DAMAGE;

			return true;
		}
	}

	return false;
}
void Spirit::setHP(int hp) {
	m_hp = hp;
}
void Spirit::setSpeed(float speed) {
	m_speed = speed;
}

int	Spirit::getHP() {
	return m_hp;
}
float Spirit::getSpeed() {
	return m_speed;
}