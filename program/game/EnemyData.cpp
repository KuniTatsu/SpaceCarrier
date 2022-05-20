#include "EnemyData.h"
#include"Factory.h"

EnemyData::EnemyData(int Id, int Type, std::string Name, float Hp, float Attack, float Defence, float Speed, std::string GhPass, Factory::MOVETYPE Move, Factory::SHOOTTYPE Shoot)
{
	id = Id;
	type = Type;
	name = Name;
	hp = Hp;
	attack = Attack;
	defence = Defence;
	speed = Speed;
	ghPass = GhPass;
	move = Move;
	shoot = Shoot;
}

EnemyData::EnemyData(int Id, int Type, std::string Name, float Hp, float Attack, float Defence, float Speed, std::string GhPass, Factory::MOVETYPE Move, Factory::SHOOTTYPE Shoot, Factory::SHOOTTYPE ExShoot)
{
	id = Id;
	type = Type;
	name = Name;
	hp = Hp;
	attack = Attack;
	defence = Defence;
	speed = Speed;
	ghPass = GhPass;
	move = Move;
	shoot = Shoot;
	exShoot = ExShoot;
}

EnemyData::~EnemyData()
{
}
