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

#include "tinyxml2/tinyxml2.h"

using namespace tds;

DECLARE_SINGLETON_MEMBER(GameManager);

GameManager::GameManager()
{
	initXMLConfigure(
		FileUtils::getInstance()->fullPathForFilename("Lvl.xml").c_str());
}


GameManager::~GameManager()
{
	CC_SAFE_RELEASE(m_SpeciallyEffectLayer);
	CC_SAFE_RELEASE(m_GameLayer);
	CC_SAFE_RELEASE(m_ShowNextLayer);
	CC_SAFE_RELEASE(m_OperateLayer);
}

bool GameManager::initXMLConfigure(std::string path)
{
	bool ret = false;

	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();

	tinyxml2::XMLError errorID = doc->LoadFile(path.c_str());

	if (errorID != 0){
		CCLOG("Parse xml Error");
		return ret;
	}

	tinyxml2::XMLElement* root = doc->RootElement();

	auto layer_index = 1;

	for (tinyxml2::XMLElement* chd = root->FirstChildElement(); chd; chd = chd->NextSiblingElement())
	{
		//CCLOG("chd : %s", chd->Name());
		const char* str_layer = chd->Attribute("layer");
		int layer = str_layer == NULL ? layer_index++ : atoi(str_layer);

		const char* bgcolor = chd->Attribute("bgColor");
		const char* levelsize = chd->Attribute("levelSize");
		m_levelConfigure[layer]["bgColor"] = bgcolor == NULL ? "0x000000" : bgcolor;
		m_levelConfigure[layer]["levelSize"] = levelsize == NULL ? "400" : levelsize;
		//[5.3] 遍历子元素的属性 id
		// FirstAttribute() : 获取 chd元素          的第一个属性
		// Next()           : 获取 chd元素的attr属性 的下一个属性
		//for (const tinyxml2::XMLAttribute* attr = chd->FirstAttribute(); attr; attr = attr->Next()) {
			// Name()  : 属性名称
			// Value() : 属性值
		//	CCLOG("chd_attr : %s , %s", attr->Name(), attr->Value());
		//}

		// 也可以通过属性名称，来获取属性值
		// CCLOG("id = %s", chd->Attribute("id"));

		//[5.4] 遍历子元素chd的子元素 <name> , <age>
		for (tinyxml2::XMLElement* e = chd->FirstChildElement(); e; e = e->NextSiblingElement()) {
			// 子元素e 为文本内容
			const tinyxml2::XMLAttribute* eattr = e->FirstAttribute();
			while (eattr){
				//CCLOG("%s=>%s", e->Name(), e->Value());
				m_levelEnemyConfigure[layer][e->Name()][eattr->Name()] = eattr->Value();
				/*
				///configure food
				if (! std::string("Food").compare(e->Name()) ){

					int num = atoi(e->Attribute("num"));
					int foodType = atoi(e->Attribute("foodType"));
					float experienceValueHold = atof(e->Attribute("experienceValueHold"));

					m_levelEnemyConfigure[layer]["Food"]["num"] = e->Attribute("num");

				}

			///configure enemy
				if( (!std::string("Fish").compare(e->Name()))
					|| ((!std::string("Jellyfish").compare(e->Name())))
					){

					int num = atoi(e->Attribute("num"));
					float hpmax = atof(e->Attribute("hpMax"));
					float speed = atof(e->Attribute("speed"));
					float experienceValueHold = atof(e->Attribute("experienceValueHold"));
					int   secondTurn = atoi(e->Attribute("secondTurn"));

				}
				*/

				eattr = eattr->Next();
			}

		}
	}


	delete doc;
	return ret;
}


void GameManager::goNextLayer()
{
	m_SpeciallyEffectLayer->onSetColor(m_GameLayer->getCurrentLayer());
}

void GameManager::goPreLayer()
{
	m_SpeciallyEffectLayer->onSetColor(m_GameLayer->getCurrentLayer());
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

void GameManager::onPlayerRotation(double rotation)
{
	m_GameLayer->onPlayerRotation(rotation);
}