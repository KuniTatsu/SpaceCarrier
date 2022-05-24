#pragma once
#include"PartsBase.h"
#include<memory>

class ShootBase;
class Player;

class WeaponParts :public PartsBase
{
public:
	//id(int)	PartsType(int)	Parts_Name	Atack(int)	CoolDawn(float)	BulletType(enum) Gh(std::string)
	WeaponParts(int Id, int PartsType, std::string Name, float Attack, float CoolDawn, std::string ShootType, std::string GhPass);

	~WeaponParts();

	//弾を撃つ関数
	void ShootBullet(const float Deltatime);

	//船改造画面での描画関数
	void DrawParts(int X, int Y);

protected:

	//パーツの追加攻撃力
	float attack = 0;

	enum class SHOOTTYPE {
		STRAIGHT,
		MISSILE,
		/*FOCUS,
		FAST,*/
		MAX
	};

	//SHOOTTYPE myShootType = SHOOTTYPE::STRAIGHT;

	ShootBase* myShoot = nullptr;

	std::shared_ptr<Player>player = nullptr;

};

