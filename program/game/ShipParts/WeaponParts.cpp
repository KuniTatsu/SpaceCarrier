#include "WeaponParts.h"
#include"../StrategyPattern/ShootPattern.h"
#include"../../dxlib_ext/dxlib_ext.h"
#include"../Object/Player.h"
#include"../Manager/GameManager.h"

WeaponParts::WeaponParts(int Id, int PartsType, std::string Name, float Attack, float CoolDawn, std::string ShootType, std::string GhPass)
{
	gManager = GameManager::Instance();
	player = gManager->GetPlayer();

	if (ShootType == "STRAIGHT") {

		tnl::Vector3 vPos = { 0,-5,0 };

		myShoot = new StraightShoot(vPos, CoolDawn);
	}
	else if (ShootType == "MISSILE") {

		tnl::Vector3 vPos = { 8.0f,0,0 };

		myShoot = new TrackShoot(vPos, CoolDawn);
	}
	partsId = Id;
	partsType = PartsType;
	partsName = Name;

	attack = Attack;
	gh = gManager->LoadGraphEx(GhPass);


}

WeaponParts::~WeaponParts()
{
	delete myShoot;
}

void WeaponParts::ShootBullet(const float Deltatime)
{
	myShoot->Shoot(player->GetPos(), player->GetRadius(), gManager->deltatime);
}

void WeaponParts::DrawParts(int X, int Y)
{
	DrawRotaGraph(X, Y, 1, 0, gh, true);
}
