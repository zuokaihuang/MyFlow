//
//  GameManager.h
//  HelloWorldDemo
//
//  Created by yons on 15/4/4.
//
//

#ifndef HelloWorldDemo_GameManager_h
#define HelloWorldDemo_GameManager_h

#include <unordered_map>
#include "Singleton.h"
#include "cocos2d.h"
USING_NS_CC;
using std::unordered_map;


namespace tds {


	

	class SpeciallyEffectLayer;
	class ShowNextLayer;
	class GameLayer;
	class RandomRunRole;
	class OperateLayer;

	class GameManager : public Singleton<GameManager>{

	public:
		GameManager();
		~GameManager();
		bool initXMLConfigure(std::string path);
	public:
		SpeciallyEffectLayer	*m_SpeciallyEffectLayer;
		GameLayer			*m_GameLayer;
		ShowNextLayer			*m_ShowNextLayer;
		OperateLayer			*m_OperateLayer;

	public:
		void goNextLayer();
		void goPreLayer();

		void checkCollision(RandomRunRole* pRole);

		void onPlayerMove(cocos2d::Vec2 direction, float distance);
		void onSPELayerMove(cocos2d::Vec2 direction, float distance);
		void onPlayerStop();
		void onSPELayerStop();
		void onPlayerRotation(double rotation);

		/*
			<Level layer="1">
				<Food  num="3"/>
				<Fish  num="3"/>
				<... />
			</Level>

			<Level layer="2">
				<Food num="3"/>
				<Fish num="3"/>
				<... />
			</Level>

		*/
		unordered_map<int, unordered_map<std::string, std::string>> m_levelConfigure;
		unordered_map<int, 
			unordered_map<std::string, 
			unordered_map<std::string, std::string>> > m_levelEnemyConfigure;

	};

#define g_GameManager GameManager::Instance()




};//end namespace tds
#endif
