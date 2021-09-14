/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSFinal.h"
#include "GSMap1.h"
#include "GSWin.h"
#include "GSGameOver.h"
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSCredit.h"
#include "GameStatebase.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		break;
	case StateType::STATE_CREDIT:
		gs = std::make_shared<GSCredit>();
		break;
	case StateType::STATE_OVER:
		gs = std::make_shared<GSGameOver>();
		break;
	case StateType::STATE_WIN:
		gs = std::make_shared<GSWin>();
		break;
	case StateType::STATE_MAP1:
		gs = std::make_shared<GSMap1>();
		break;
	case StateType::STATE_MAP2:
		gs = std::make_shared<GSFinal>();
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}