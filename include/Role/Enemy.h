
#ifndef _ENEMY_H__
#define _ENEMY_H__

#include "RandomRunRole.h"
#include <unordered_map>
using std::unordered_map;

namespace tds{

	class Enemy : public RandomRunRole
	{
	public:
		//CREATE_FUNC(Enemy);
		//virtual bool init(std::string type = "");
		//virtual std::string getPath(){ return ""; }
		void initFromConfigure(const unordered_map<std::string, std::string>& prop_map);

	private:
		
	};

	class Food : public Enemy
	{
	public:
		Food(int fooType = 2) :Enemy(), m_FoodType(fooType){}
		static Food* create(int foodType = 2);
		CC_SYNTHESIZE(int,m_FoodType,FoodType);
		virtual std::string getPath();
		//virtual bool init();
	};

	class SpawnFish : public Enemy
	{
	public:
		CREATE_FUNC(SpawnFish);
		virtual std::string getPath(){ return "Fish2.png"; }
	};

	class SpawnJellyfish : public Enemy
	{
	public:
		CREATE_FUNC(SpawnJellyfish);
		virtual std::string getPath(){ return "Jellyfish2.png"; }
	};

	class SpawnFlockfish : public Enemy
	{
	public:
		CREATE_FUNC(SpawnFlockfish);
		virtual std::string getPath(){ return "Flockfish.png"; }
	};


	class EnemyFactory
	{
	public:
		static Enemy* create(std::string type);

	private:
		
	};

};


#endif
