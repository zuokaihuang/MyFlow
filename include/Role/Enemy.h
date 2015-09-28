
#ifndef _ENEMY_H__
#define _ENEMY_H__

#include "RandomRunRole.h"

namespace tds{

	class Enemy : public RandomRunRole
	{
	public:
		//CREATE_FUNC(Enemy);
		//virtual bool init(std::string type = "");
		//virtual std::string getPath(){ return ""; }
	private:
		
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
