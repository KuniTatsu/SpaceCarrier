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

	//����̃N�[���_�E���X�V�֐�
	void WeaponUpdate();

	//����̃N�[���_�E���擾�֐�
	float GetWeaponCoolDawn();

	//�e�����֐�
	void ShootBullet(const float Deltatime);

	//�D������ʂł̕`��֐�
	void DrawParts(int X, int Y);

	//����p�[�c�𐶐����邽�߂ɕK�v�Ȃ��ׂĂ̏����擾����֐�
	inline std::tuple<int, int, std::string, float, float, std::string, std::string>GetAllWeaponData() {
		return{ partsId, partsType, partsName, attack,coolDown, shootType,ghPass };
	}

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

	//�}�X�^�[�f�[�^�Q�Ɨp
	std::string shootType = "";
	std::string ghPass = "";
	float coolDown = 0.0f;

};

