
#ifndef _SPECIALLYEFFECTLAYER_H__
#define _SPECIALLYEFFECTLAYER_H__

#include "BaseLayer.h"

namespace tds{

	class SpeciallyEffectLayer : public BaseLayer
	{
	public:
		virtual void onEnter();
		virtual void onExit();
		void			onSetColor(bool next_or_pre);
		CREATE_FUNC(SpeciallyEffectLayer);
		CC_SYNTHESIZE(cocos2d::Vec2, m_Velocity, Velocity);
		void updateSelf();
		
	private:
		SpeciallyEffectLayer();
		~SpeciallyEffectLayer();
		virtual bool init();

		

		cocos2d::LayerColor* m_layer;
		size_t			   m_nextLayerColorIndex;
	};


};//end namespace std

#endif