//enemyのマスターデータ

#pragma once
#include<string>
#include"Factory.h"


class EnemyData
{
public:
	//****注意!!!!このクラスはマスターデータ用です*****//
	EnemyData(int Id, int Type, std::string Name, float Hp, float Attack, float Defence, float Speed,
		std::string GhPass, Factory::MOVETYPE Move, Factory::SHOOTTYPE Shoot);
	EnemyData(int Id, int Type, std::string Name, float Hp, float Attack, float Defence, float Speed,
		std::string GhPass, Factory::MOVETYPE Move, Factory::SHOOTTYPE Shoot, Factory::SHOOTTYPE ExShoot);
	~EnemyData();

	//MoveType取得関数
	inline Factory::MOVETYPE GetMoveType() {
		return move;
	}
	//射撃パターン取得関数	
	inline Factory::SHOOTTYPE GetShootType() {
		return shoot;
	}
	//特殊射撃パターン取得関数	
	inline Factory::SHOOTTYPE GetExShootType() {
		return exShoot;
	}
	//ステータス配列取得関数
	inline float* GetStatus() {
		return status;
	}
	//GhPass取得関数
	inline std::string GetGhPass() {
		return ghPass;
	}

private:
	int id = 0;
	int type = 0;
	std::string name = "";

	//---status---
	float hp = 0;
	float attack = 0;
	float defence = 0;
	float speed = 0;

	float status[4] = {};
	//------------
	std::string ghPass = "";

	Factory::MOVETYPE move;

	Factory::SHOOTTYPE shoot;
	Factory::SHOOTTYPE exShoot;


};

