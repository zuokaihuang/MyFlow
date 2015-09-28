
#ifndef _SHOWNEXTLAYER_H__
#define _SHOWNEXTLAYER_H__

#include "BaseLayer.h"

namespace tds{

	class ShowNextLayer : public BaseLayer
	{
	public:
		virtual void onEnter();
		virtual void onExit();
	private:
		ShowNextLayer();
		~ShowNextLayer();
		virtual bool init();
	};

};//end namespace tds;

#endif
