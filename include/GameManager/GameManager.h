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
	class GameLayer;

	class GameManager : public Singleton<GameManager>{

	public:
		GameManager();
		~GameManager();

	public:
		SpeciallyEffectLayer	*m_SpeciallyEffectLayer;
		GameLayer			*m_GameLayer;


	public:
		void goNextLayer();
		void goPreLayer();
	};

#define g_GameManager GameManager::Instance()




};//end namespace tds
#endif
