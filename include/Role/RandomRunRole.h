
#ifndef _RANDOMRUNROLE_H__
#define _RANDOMRUNROLE_H__

#include "Role.h"

namespace tds{

	class RandomRunRole : public Role
	{
	protected:
		RandomRunRole(std::string name = "");
		virtual bool init(std::string name = "");
		virtual std::string getPath(){ return ""; }

	public:
		CC_SYNTHESIZE(bool, m_CanRun,CanRun);
		void onMoveCallBack();
		virtual void beginRandomRun();

		virtual void update(float dt);
	};

};



#endif