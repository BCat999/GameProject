#include "Enemy.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"
#include "../GameManager/ResourceManagers.h"


Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrames,
	float frameTime, Type type) : AnimationSprite(model, shader, texture, numFrames,frameTime),m_type(type){
	Init();
}
Enemy :: ~Enemy() {

}
void Enemy::Init() {
	if (m_type == Type::Worm) {
		m_shootInterval = 1.0f;
		m_shootTime = 0.0f;
		SetTexture(ResourceManagers::GetInstance()->GetTexture("worm-move.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		setSpeed(1);
		setNumFrames(4);
		setHP(10);
		SetSize(80, 50);
	}
	else if (m_type == Type::HealtGrass) {
		m_shootInterval = 2.0f;
		m_shootTime = 0.0f;
		SetTexture(ResourceManagers::GetInstance()->GetTexture("healthGrass.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		setNumFrames(7);
		setSpeed(0);
		setHP(15);
		SetSize(50, 100);
	}
	else if (m_type == Type::Boss) {
		m_shootInterval = 2.0f;
		m_shootTime = 0.0f;
		Set2DPosition(Globals::screenWidth / 2+50, GROUND-50);
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Boss1-awake-base.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		setNumFrames(6);
		setSpeed(0.001);
		setHP(BOSS_MAX_HP);
		SetSize(200, 200);
	}

}

void Enemy::Move(float x,float deltatime) {

	if (m_type == Type::Worm) {
		Update(deltatime);
		setSpeed(1);
		SetTexture(ResourceManagers::GetInstance()->GetTexture("worm-move.tga"));
		if (x >= m_position.x) {
			m_position.x += m_speed;
		}
		else {
			
			m_position.x -= m_speed*deltatime;
			
		}
		Set2DPosition(m_position.x, m_position.y);
		
	}
	else if (m_type == Type::Boss) {
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Boss.tga"));
		if (x >= m_position.x) {
			m_position.x += m_speed;
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


void Enemy::UpdateTimeCountDown(GLfloat deltaTime) {
	m_shootTime += deltaTime;
	
}
void Enemy::Attack(float x, float deltatime) {
	if (m_type == Type::Worm) {
		setSpeed(0);
		if (x >= m_position.x) {
			SetTexture(ResourceManagers::GetInstance()->GetTexture("worm-attack.tga"));

		}
		else {
			SetTexture(ResourceManagers::GetInstance()->GetTexture("worm-attack-back.tga"));
		}
		Update(deltatime);
	}
	else if (m_type==Type::Boss) {
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Boss1-Attack.tga"));
		Update(deltatime);
	}
	
		
}
void Enemy::Health(std::shared_ptr<Enemy>	enemy) {
	enemy->setHP(enemy->getHP() + GRASS_HEALTH);
}
bool Enemy::getHitFire(int x, int y, int w, int h) {
	for (int i = x - w/2; i < x + w / 2; i++) {
		if ((i >= m_position.x - 10) && (i <= m_position.x + 10) && (y < m_position.y + m_iHeight) && (y> m_position.y - m_iHeight)) {
			m_hp -= FOX_DAMAGE;

			return true;
		}
	}
		
	return false;
}
void Enemy::setHP(int hp) {
	m_hp = hp;
}
void Enemy::setSpeed(float speed) {
	m_speed = speed;
}

int	Enemy::getHP() {
	return m_hp;
}
float Enemy::getSpeed() {
	return m_speed;
}