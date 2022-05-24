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

	//�e�����֐�
	void ShootBullet(const float Deltatime);

	//�D������ʂł̕`��֐�
	void DrawParts(int X, int Y);

protected:

	//�p�[�c�̒ǉ��U����
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

