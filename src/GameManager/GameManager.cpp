//
//  GameManager.cpp
//  HelloWorldDemo
//
//  Created by yons on 15/4/4.
//
//

#include "GameManager.h"
#include "SpeciallyEffectLayer.h"
#include "GameLayer.h"

using namespace tds;

DECLARE_SINGLETON_MEMBER(GameManager);

GameManager::GameManager()
{
      
}


GameManager::~GameManager()
{
	CC_SAFE_RELEASE(m_SpeciallyEffectLayer);
	CC_SAFE_RELEASE(m_GameLayer);
}

void GameManager::goNextLayer()
{
	m_SpeciallyEffectLayer->onSetColor(true);
}

void GameManager::goPreLayer()
{
	m_SpeciallyEffectLayer->onSetColor(false);
}