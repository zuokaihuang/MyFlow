#ifndef __HelloWorldDemo__OperateLayer__
#define __HelloWorldDemo__OperateLayer__

#include "cocos2d.h"

namespace tds{

	class OperateLayer : public cocos2d::Layer
	{
	public:
		OperateLayer();
		~OperateLayer();
		virtual bool init();

		CREATE_FUNC(OperateLayer);
	};
};// end namespace tds
#endif