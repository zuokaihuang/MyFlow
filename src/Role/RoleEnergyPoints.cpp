
#include "RoleEnergyPoints.h"
#include "GameManager.h"

using namespace tds;

bool EnergyPoints::init()
{
	bool ret = false;

	do{
		this->initWithFile("images/food/Food1.png");
		this->scheduleUpdate();
		ret = true;
	} while (0);

	return ret;
}

void EnergyPoints::update(float dt)
{
	g_GameManager->checkCollisionWithEnergyPoints(this);
}