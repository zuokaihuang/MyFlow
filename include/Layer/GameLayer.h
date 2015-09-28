
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

		void AddFish(std::string fishtype,size_t numbers);

		CREATE_FUNC(GameLayer);

	private:
		GameLayer();
		~GameLayer();
		virtual bool init();

		void onConnect(float dt);
		void RemoveSignal(float dt);

		void NextLayer();
		void PreLayer();
		void onMoveCallBack(float dt);
	};


};



#endif

