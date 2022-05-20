//enemy�̃}�X�^�[�f�[�^

#pragma once
#include<string>

class Factory;

class EnemyData
{
public:
	//****����!!!!���̃N���X�̓}�X�^�[�f�[�^�p�ł�*****//
	EnemyData(int Id,int Type,std::string Name, float Hp, float Attack, float Defence, float Speed, 
					std::string GhPass,Factory::MOVETYPE Move,Factory::SHOOTTYPE Shoot);
	EnemyData(int Id, int Type, std::string Name, float Hp, float Attack, float Defence, float Speed,
		std::string GhPass, Factory::MOVETYPE Move, Factory::SHOOTTYPE Shoot, Factory::SHOOTTYPE ExShoot);
	~EnemyData();

	//MoveType�擾�֐�
	inline Factory::MOVETYPE GetMoveType() {
		return move;
	}
	inline Factory::SHOOTTYPE GetShootType() {
		return shoot;
	}
	inline Factory::SHOOTTYPE GetExShootType() {
		return exShoot;
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
	//------------
	std::string ghPass = "";

	Factory::MOVETYPE move;

	Factory::SHOOTTYPE shoot;
	Factory::SHOOTTYPE exShoot;


};

