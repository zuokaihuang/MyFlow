
#ifndef _SPECIALLYEFFECTLAYER_H__
#define _SPECIALLYEFFECTLAYER_H__
#include <unordered_map>
#include "BaseLayer.h"
using std::unordered_map;

namespace tds{

	class SpeciallyEffectLayer : public BaseLayer
	{
	public:
		virtual void onEnter();
		virtual void onExit();
		void			onSetColor(int layer);
		CREATE_FUNC(SpeciallyEffectLayer);
		CC_SYNTHESIZE(cocos2d::Vec2, m_Velocity, Velocity);
		void updateSelf(float duration);
		void initBgColorFromConfigure();
	private:
		SpeciallyEffectLayer();
		~SpeciallyEffectLayer();
		virtual bool init();


		
		unordered_map<int, cocos2d::Color3B> _level_BgColor;

		cocos2d::LayerColor* m_layer;
		size_t			   m_nextLayerColorIndex;
	};


};//end namespace std

#endif