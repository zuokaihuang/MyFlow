
#ifndef _CIRCLEMOVEACTION_H__
#define _CIRCLEMOVEACTION_H__

#include "cocos2d.h"
USING_NS_CC;

namespace tds{
	
	class  CircleMoveAction : public cocos2d::ActionInterval
	{
	public:
		CircleMoveAction(){};
		static CircleMoveAction* create(float t, cocos2d::Point circleCenter,float radius);
		virtual bool init(float t,cocos2d::Point circleCenter,float radius);

		virtual void update(float dt);

	protected:
		cocos2d::Point m_center;
		float		  m_radius;
		float		  m_radian;
		float		  m_moveTimes;

	};

};//end namespace tds;


#endif

