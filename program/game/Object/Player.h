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
	
	void ShootBullet();
private:

	void Move();

	//���L�[�̔z��
	const tnl::Input::eKeys arrowKeys[static_cast<int>(DIR::MAX)] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT, 
																		tnl::Input::eKeys::KB_DOWN, tnl::Input::eKeys::KB_LEFT };

	//�L�[�擾
	inline tnl::Input::eKeys GetKeys(int KeyNum){
		return arrowKeys[KeyNum];
	}

	//void SetMoveAmount();

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
	
	//�e���ˊԊu
	const float SHOOTCOOLDOWN = 0.01f;
	//�e���˃^�C�}�[
	float shootTimer = 0.0f;

	//obj�t�@�N�g���[�|�C���^
	Factory* fac = nullptr;
};

