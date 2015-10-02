
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
Food* Food::create(int foodType)
{
	Food* food = new Food(foodType);

	if (food && food->init())
	{
		food->autorelease();
		return food;
	}
	else{
		delete food;
		food = NULL;
		return NULL;
	}
}

std::string  Food::getPath()
{
	const char* formatStr = "Food%d.png";

	const char* path = String::createWithFormat(formatStr, m_FoodType)->getCString();

	return std::string(path);
}

void Enemy::initFromConfigure(const unordered_map<std::string, std::string>& prop_map)
{
	auto prop = prop_map.find("speed");
	String prop_value;

	if (prop != prop_map.end()){
		prop_value = prop->second;
		this->setMoveSpeed(prop_value.floatValue());
	}

	prop = prop_map.find("hpMax");
	if (prop != prop_map.end()){
		prop_value = prop->second;
		this->setMaxHP(prop_value.floatValue());
	}

	prop = prop_map.find("experienceValueHold");
	if (prop != prop_map.end()){
		prop_value = prop->second;
		this->setExperienceValueHold(prop_value.floatValue());
	}

	prop = prop_map.find("secondTurn");
	if (prop != prop_map.end()){
		prop_value = prop->second;
		this->setTurnCooldown(prop_value.intValue());
	}

}



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
	ret->setName(type);
	return ret;
}

