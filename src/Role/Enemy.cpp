
#include "Enemy.h"

using namespace tds;

USING_NS_CC;

/*
bool Enemy::init(std::string type)
{
	bool ret = false;
	do{
		auto path = getPath();
		if (!path.empty())
			this->initWithFile(path);
		else
			return ret;

		ret = true;
	} while (0);
	return ret;
}

*/

Enemy* EnemyFactory::create(std::string type)
{
	Enemy* ret = nullptr;

	if ("Fish" == type){
		ret = SpawnFish::create();
	}
	else if ("Jellyfish" == type){
		ret = SpawnJellyfish::create();
	}
	else if ("Flockfish" == type){
		ret = SpawnFlockfish::create();
	}else{
		ret = SpawnFish::create();
	}

	return ret;
}

