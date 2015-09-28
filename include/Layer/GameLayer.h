
#ifndef _GAMELAYER_H__
#define _GAMELAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"

namespace tds{

	class GameLayer : public BaseLayer
	{
	public:

		void AddPlayer(size_t numbers = 1);
		void AddNPC(size_t numbers = 2);

		void AddFish(std::string fishtype, size_t numbers,GLubyte opacity = 255);

		CREATE_FUNC(GameLayer);

		virtual void onEnter();
		virtual void onExit();
		virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
		bool checkCollision(cocos2d::Point p);
	private:
		GameLayer();
		~GameLayer();
		virtual bool init();

		void readConfigureFile(std::string path = "");

		void onConnect(float dt);
		void RemoveSignal(float dt);

		void NextLayer();
		void PreLayer();
		void onMoveCallBack(float dt);

		void onStop(){};
	};


};



#endif

