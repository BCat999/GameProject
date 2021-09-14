#pragma once
#include "Sprite2D.h"
class AnimationSprite : public Sprite2D
{
public:
	AnimationSprite();
	AnimationSprite( std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrames,
		float frameTime);
	void		setNumFrames(int nF) {m_numFrames = nF;};
	void		setCurrentFrames(int cF) { m_currentFrame = cF; };
	void		setFrameTime(float fT) { m_frameTime = fT; };
	int			getCurrentFrames() { return m_currentFrame; };
	int			getNumFrames() { return m_numFrames; };
	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;

protected:
	int m_numFrames;
	int m_currentFrame;
	float m_frameTime;
	float m_currentFrameTime;
};

