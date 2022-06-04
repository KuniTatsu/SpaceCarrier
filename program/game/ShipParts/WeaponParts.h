#pragma once
#include"PartsBase.h"
#include<memory>
#include<string>
#include<tuple>

class ShootBase;
class Player;

class WeaponParts :public PartsBase
{
public:
	//id(int)	PartsType(int)	Parts_Name	Atack(int)	CoolDawn(float)	BulletType(enum) Gh(std::string)
	WeaponParts(int Id, int PartsType, std::string Name, float Attack, float CoolDawn, std::string ShootType, std::string GhPass, std::string IconGhPass);

	~WeaponParts();

	//武器のクールダウン更新関数
	void WeaponUpdate();

	//武器のクールダウン取得関数
	float GetWeaponCoolDawn();

	//弾を撃つ関数
	void ShootBullet(const float Deltatime);

	//船改造画面での描画関数
	void DrawParts(int X, int Y);

	//武器パーツを生成するために必要なすべての情報を取得する関数
	inline std::tuple<int, int, std::string, float, float, std::string, std::string>GetAllWeaponData() {
		return{ partsId, partsType, partsName, attack,coolDown, shootType,ghPass };
	}

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

	//マスターデータ参照用
	std::string shootType = "";
	std::string ghPass = "";
	float coolDown = 0.0f;

};

