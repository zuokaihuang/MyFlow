
#include "NPC.h"
#include "GameManager.h"

using namespace tds;

BaseNPC::BaseNPC(std::string name)
:RandomRunRole(name)
{

}

void BaseNPC::checkCollision()
{
	if (this->isVisible() && this->getOpacity()> 20)
		g_GameManager->checkCollision(this);
}