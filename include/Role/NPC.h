

#ifndef _BASE_NPC_H__
#define _BASE_NPC_H__

#include "RandomRunRole.h"

namespace tds{

	class BaseNPC : public RandomRunRole
	{
	protected:
		BaseNPC(std::string name);
		//~BaseNPC();
		virtual void checkCollision(){};
	};

};


#endif