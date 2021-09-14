#include "Fox.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Application.h"
#include "Scratch.h"
#include "../GameManager/ResourceManagers.h"


Fox::Fox(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrames,
	float frameTime) : AnimationSprite(model, shader, texture, numFrames, frameTime) {
	Init();
}
Fox :: ~Fox() {

}

void Fox::Init() {
	setHP(50);
	m_shootInterval = 0.5f;
	m_shootTime = 0.0f;
	SetTexture(ResourceManagers::GetInstance()->GetTexture("fox-run.tga"));
	SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
	Set2DPosition(100, GROUND-10);
	SetSize(150, 80);
}

void Fox::Move(GLfloat deltaTime,int key) {
	
	if (key == KEY_MOVE_LEFT) {
		Set2DPosition(m_position.x - FOX_SPEED, m_position.y);
		SetTexture(ResourceManagers::GetInstance()->GetTexture("fox-run-back.tga"));
		Update(deltaTime);
	}
	else if (key== KEY_MOVE_RIGHT) {
		Set2DPosition(m_position.x + FOX_SPEED, m_position.y);
		SetTexture(ResourceManagers::GetInstance()->GetTexture("fox-run.tga"));
		Update(deltaTime);
	}

}
void Fox::UpdateTime(GLfloat deltaTime) {
	m_shootTime += deltaTime;
}


void Fox::Shoot(bool dic, int k) {
	if (m_shootTime >= m_shootInterval) {
		m_shootTime = 0;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		std::shared_ptr<Fire>	m_fire;
		if (k == KEY_SHOT) {
			
			auto texture = ResourceManagers::GetInstance()->GetTexture("Bullet.tga");
			m_fire = std::make_shared<Fire>(model, shader, texture, Skill::Fire);
			m_fire->SetSize(50, 50);
			m_fire->Set2DPosition(m_position.x, m_position.y);
			if (!dic) m_fire->setDir(-1);
			else m_fire->setDir(1);
			m_listFire.push_back(m_fire);
		}
		else if (k == KEY_SCRATCH) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("sctR.tga");
			m_fire = std::make_shared<Fire>(model, shader, texture, Skill::Scratch);
			m_fire->SetSize(80, 80);
			m_fire->Set2DPosition(m_position.x, m_position.y);
			if (!dic) { 
				m_fire->SetTexture(ResourceManagers::GetInstance()->GetTexture("sctL.tga"));
				m_fire->Set2DPosition(m_position.x - m_iWidth / 2 - 10, m_position.y); }
				
			else {
				m_fire->SetTexture(ResourceManagers::GetInstance()->GetTexture("sctR.tga"));
				m_fire->Set2DPosition(m_position.x + m_iWidth / 2 + 10, m_position.y);
			}
		}
		m_listFire.push_back(m_fire);

	}
}
std::list<std::shared_ptr<Fire>> Fox::getFire() {
	return m_listFire;
}
void Fox::setHP(int hp) {
	m_hp = hp;
}

bool Fox::getHit(std::shared_ptr<Enemy>	enemy) {
	for (int i = (enemy->GetPositionX() - enemy->getXWidth() / 2); i < (enemy->GetPositionX() + enemy->getXWidth() / 2); i++) {
		if ((i >= m_position.x - m_iWidth / 2) && (i <= m_position.x + m_iWidth / 2) && (enemy->GetPositionY() < m_position.y + m_iHeight ) && (enemy->GetPositionY() > m_position.y - m_iHeight)) {
		if(enemy->getType()==Type::Boss)	m_hp -= 5;
			m_hp -= 1;
		return true;
		}
	}
	
	return false;
}
bool Fox::getSP(std::shared_ptr<Spirit>	sp) {
	if (sp->getType() == State::BOSS) {
		for (int i = (sp->GetPositionX() - sp->getXWidth() / 2); i < (sp->GetPositionX() + sp->getXWidth() / 2); i++) {
			if ((i >= m_position.x - m_iWidth / 2) && (i <= m_position.x + m_iWidth / 2) && (sp->GetPositionY()+100 < m_position.y + m_iHeight) && (sp->GetPositionY()+100 > m_position.y - m_iHeight)) {
				m_hp -= 5;
				return true;
			}
		}
	}
	else {
		for (int i = (sp->GetPositionX() - sp->getXWidth() / 2); i < (sp->GetPositionX() + sp->getXWidth() / 2); i++) {
			if ((i >= m_position.x - m_iWidth / 2) && (i <= m_position.x + m_iWidth / 2) && (sp->GetPositionY() < m_position.y + m_iHeight) && (sp->GetPositionY() > m_position.y - m_iHeight)) {
				return true;
			}
		}
	}

	return false;
}