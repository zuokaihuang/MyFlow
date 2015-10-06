
#include "NextLayerNPC.h"
using namespace tds;
USING_NS_CC;

NextLayerNPC::NextLayerNPC()
:BaseNPC("NextLayerNPC")
{

}

/*
NextLayerNPC::~NextLayerNPC()
{

}
*/

bool NextLayerNPC::init()
{
	bool ret = false;

	do{
		this->initWithFile("images/npc/NextLayerNPC.png");
		this->scheduleUpdate();
		ret = true;
	} while (0);

	return ret;
}




