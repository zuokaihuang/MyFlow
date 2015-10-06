
#ifndef _ROLEENERGYPOINTS_H__
#define _ROLEENERGYPOINTS_H__

#include "cocos2d.h"
#include "Role.h"
namespace tds
{
	class EnergyPoints : public cocos2d::Sprite
	{
	public:
		EnergyPoints(){};
		~EnergyPoints()
		{
			CC_SAFE_RELEASE(m_owner);
		}
		CREATE_FUNC(EnergyPoints);
		virtual bool init();
		virtual void update(float dt);

		CC_SYNTHESIZE(Role*,m_owner,WhoOwnerThisEnergyPonit);

	public:
	};


};//end namespace tds


#endif
