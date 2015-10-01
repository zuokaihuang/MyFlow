//
//  GameManager.h
//  HelloWorldDemo
//
//  Created by yons on 15/4/4.
//
//

#ifndef HelloWorldDemo_GameManager_h
#define HelloWorldDemo_GameManager_h

#include "Singleton.h"
#include "cocos2d.h"
USING_NS_CC;



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

	};

#define g_GameManager GameManager::Instance()




};//end namespace tds
#endif
