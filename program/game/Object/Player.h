#pragma once
#include"Object.h"
#include<memory>
#include<math.h>

class GameManager;
class Factory;

class Player final :public Object
{
public:
	Player();
	~Player();

	void Update()override;
	void Draw()override;
	void Init()override;
	void CheckIsLive()override;
	//�e���ˊ֐�
	void ShootBullet();
	//���q���x�擾�֐�
	inline const float GetCruizeSpeed() {
		return CruizeSpeed;
	}

	//�׏d��(�׏d��/�ő剻�d��)���擾����֐�
	inline const float GetCapaciryRate() {
		return (haveCapacity / maxCapacity);
	}
private:

	void Move();

	//���L�[�̔z��
	const tnl::Input::eKeys arrowKeys[static_cast<int>(DIR::MAX)] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT,
																		tnl::Input::eKeys::KB_DOWN, tnl::Input::eKeys::KB_LEFT };

	//�L�[�擾
	inline tnl::Input::eKeys GetKeys(int KeyNum) {
		return arrowKeys[KeyNum];
	}

	//---------------��ʓ��ړ��֌W---------------------//

	//�ꎞ�ۊǗpX�ړ���
	float moveX = 0.0f;
	//�ꎞ�ۊǗpY�ړ���
	float moveY = 0.0f;
	//
	//float fixMoveAmount = 0.0f;

	//�ړ��X�s�[�h
	const int SPEED = 5;

	//�ړ��L�[���������Ƃ��̈ړ���
	const int MOVEAMOUNT[static_cast<int>(DIR::MAX)] = { -SPEED,SPEED,SPEED,-SPEED };

	//�P�ʃx�N�g���擾�֐�
	inline tnl::Vector3 GetFixVector(float X, float Y) {

		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);

	}

	//---------------------------------------------------//

	//�e���ˊԊu
	const float SHOOTCOOLDOWN = 0.1f;
	//�e���˃^�C�}�[
	float shootTimer = 0.0f;

	//�e���˃|�C���g�␳
	const float INITPOSY = 25.0f;


	//�q�s�X�s�[�h �X�e�[�W�����S�[���֌������X�s�[�h
	float CruizeSpeed = 0;

	//---------------�׏d�֌W---------------------------//
	//�׏d�ő�� �׏d�ʂ�����𒴂���ƍq�s�X�s�[�h�Ƀy�i���e�B���t��
	float maxCapacity = 0;
	//�׏d�� �^�ԉו��̑��d�� 
	float haveCapacity = 0;

	//--------------------------------------------------//
	//obj�t�@�N�g���[�|�C���^
	Factory* fac = nullptr;
};

