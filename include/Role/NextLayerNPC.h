
#ifndef _NEXTLAYERNPC_H_
#define _NEXTLAYERNPC_H_

#include "NPC.h"

namespace tds{

	class NextLayerNPC : public BaseNPC
	{
	public:
		CREATE_FUNC(NextLayerNPC);
		virtual std::string getPath(){ return "images/npc/NextLayerNPC.png"; }

	private:
		virtual bool init();
		
		//virtual void update(float dt);
		NextLayerNPC();
		//~NextLayerNPC();

		//CC_SYNTHESIZE(cocos2d::Vec2,m_PlayerPositon,PlayerPosition);

		//void onMove();
		//void onMoveCallBack();

	};


}; //end namespace tds;


#endif
