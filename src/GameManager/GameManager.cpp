//
//  GameManager.cpp
//  HelloWorldDemo
//
//  Created by yons on 15/4/4.
//
//

#include "GameManager.h"
#include "SpeciallyEffectLayer.h"
#include "ShowNextLayer.h"
#include "GameLayer.h"
#include "RandomRunRole.h"
#include "Enemy.h"
#include "NextLayerNPC.h"
#include "PreLayerNPC.h"
#include "OperateLayer.h"

using namespace tds;

DECLARE_SINGLETON_MEMBER(GameManager);

GameManager::GameManager()
{
      
}


GameManager::~GameManager()
{
	CC_SAFE_RELEASE(m_SpeciallyEffectLayer);
	CC_SAFE_RELEASE(m_GameLayer);
	CC_SAFE_RELEASE(m_ShowNextLayer);
	CC_SAFE_RELEASE(m_OperateLayer);
}

void GameManager::goNextLayer()
{
	m_SpeciallyEffectLayer->onSetColor(true);
}

void GameManager::goPreLayer()
{
	m_SpeciallyEffectLayer->onSetColor(false);
}

void GameManager::checkCollision(RandomRunRole* pRole)
{
	auto rolePosition = pRole->getPosition();

	if(m_GameLayer->checkCollision(rolePosition))
	{
		if ("NextLayerNPC" == pRole->getName()){
			log("%s", "NextLayerNPC");
			m_GameLayer->NextLayer();

		}
		else if ("PreLayerNPC" == pRole->getName()){
			log("%s", "PreLayerNPC");
			m_GameLayer->PreLayer();

		}
		else
			pRole->removeFromParent();
	}
}



void GameManager::onPlayerMove(cocos2d::Vec2 direction, float distance)
{
	m_GameLayer->onPlayerMove(direction, distance);
}

void GameManager::onSPELayerMove(cocos2d::Vec2 direction, float distance)
{
	m_GameLayer->onSPELayerMove(direction, distance);
}

void GameManager::onSPELayerStop()
{
	m_GameLayer->onSPELayerStop();
}

void GameManager::onPlayerStop()
{
	m_GameLayer->onPlayerStop();
}
