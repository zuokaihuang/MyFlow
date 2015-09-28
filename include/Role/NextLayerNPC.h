
#ifndef _NEXTLAYERNPC_H_
#define _NEXTLAYERNPC_H_

#include "Role.h"

namespace tds{

	class NextLayerNPC : public Role
	{
	public:
		CREATE_FUNC(NextLayerNPC);
		
		//bool IsOutOffPlayerVision(cocos2d::Vec2 p);
		void Connect(cocos2d::Vec2 playerposition);

	private:
		virtual bool init();
		virtual void update(float dt);
		NextLayerNPC();
		~NextLayerNPC();

		CC_SYNTHESIZE(bool, m_UpdateTimer, UpdateTimer);
		CC_SYNTHESIZE(float, m_NextMoveTime,NextMoveTime);
		CC_SYNTHESIZE(cocos2d::Vec2,m_PlayerPositon,PlayerPosition);

		void onMove();
		void onMoveCallBack();

		cocos2d::DrawNode* m_DrawSignal;
		void onSignaling(cocos2d::Vec2 p);

		
		void onConnected(float dt);
	};


}; //end namespace tds;


#endif
