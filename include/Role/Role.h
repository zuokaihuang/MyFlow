#ifndef _ROLE_H__
#define _ROLE_H__

#include "cocos2d.h"

namespace tds{

	class Role : public cocos2d::Sprite
	{
	protected:
		Role(std::string name = "");
		virtual ~Role();

	public:
		CC_SYNTHESIZE(std::string, m_Name, Name);

	};


};//end namespace tds

#endif
