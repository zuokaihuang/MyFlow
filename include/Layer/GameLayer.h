
#ifndef _GAMELAYER_H__
#define _GAMELAYER_H__

#include "BaseLayer.h"

namespace tds{

	class BaseNPC;
	class EnergyPoints;

	class GameLayer : public BaseLayer
	{
	public:

		const static float  OPACITY;/*Opacity*/

		void AddPlayer(size_t numbers = 1);
		void AddNPC(size_t numbers = 2);
		void AddFood(size_t numbers = 10);
		void AddFish(std::string fishtype, size_t numbers,GLubyte opacity = 255);

		CREATE_FUNC(GameLayer);

		CC_SYNTHESIZE(int, m_PreLayer,		PreLayer);
		CC_SYNTHESIZE(int, m_CurrentLayer, CurrentLayer);
		CC_SYNTHESIZE(int, m_NextLayer,	NextLayer);
		virtual void update(float dt);
		virtual void onEnter();
		virtual void onExit();
		virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		virtual void onTouchMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
		virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
		bool checkCollision(cocos2d::Point p,float radius);
		bool checkCollisionWithEnergyPoints(EnergyPoints* pEnergyPoint);
		void NextLayer();
		void PreLayer();

		void onSPELayerMove(cocos2d::Vec2 direction, float distance);
		void onPlayerMove(cocos2d::Vec2 direction, float distance);
		void onSPELayerStop();
		void onPlayerStop();
		void onPlayerRotation(double rotation);
		void onUpdatePlayer(float duration);
		void onUpdateSpeciallyEffectLayer(float duration);
		void onUpdatePlayerExperienceValue(float value);
	private:
		GameLayer();
		~GameLayer();
		virtual bool init();
		
		void readConfigureFile(std::string path = "");

		void onConnect(float dt);
		void drawSignalIfNPCisOutoffVision(const BaseNPC* npc);
		void RemoveSignalNext(float dt);
		void RemoveSignalPre(float dt);

		void onMoveCallBack(float dt);

		void onStop();

		bool setAllChildrenVisibleByLayer(int layer, bool visible);
		bool setAllChildrenOpacityByLayer(int layer, GLubyte opacity, float BlurRadius = 12.0f);
		cocos2d::EventListenerMouse* _mouseListener;
		void onMouseMove(cocos2d::Event* event);

		bool checknpcOutoffPlayerVision(cocos2d::Point p);
		cocos2d::Vec2 getIntersection_NPC_and_SPELayerRect(cocos2d::Rect rect, cocos2d::Point p);
	};


};



#endif

