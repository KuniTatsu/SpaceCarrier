#include "Mod.h"

Mod::Mod(int Id, int Type, std::string Name, float Hp, float Energy, float Defence, float Speed, float Container)
{
	modId = Id;
	modType = Type;
	modName = Name;

	hp = Hp;
	energy = Energy;
	defence = Defence;
	speed = Speed;
	containerAmount = Container;

	basicStatus[0] = hp;
	basicStatus[1] = energy;
	basicStatus[2] = defence;
	basicStatus[3] = speed;
	basicStatus[4] = containerAmount;


}

Mod::~Mod()
{
}
