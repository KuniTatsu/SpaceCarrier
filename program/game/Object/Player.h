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

	//����̓G���^�[�Q�b�g����֐�
	void SetMyTarget(std::shared_ptr<Object> Target);
	//�^�[�Q�b�g������������֐�
	inline void	CleanTarget() {
		myTarget = nullptr;
	}
	//�I�[�g�^�[�Q�b�g�����X�V��؂�ւ���֐�
	inline void	ChageAutoTargerMode() {
		if (autoTargetMode) {
			autoTargetMode = false;
			return;
		}
		autoTargetMode = true;
	}
	//�I�[�g�^�[�Q�b�g�����X�V�̊m�F�֐�
	inline bool	isAutoTargetMode() {
		return autoTargetMode;
	}

	//����̖ڕW�Ɍ������Ďˌ�����֐�
	void AimShootBullet();
	void AimShootBullet(std::shared_ptr<Object>Target);

	//�U���~�T�C��
	void ShootMissile();

	//MyTarget���ݒ肳��Ă��邩�m�F����֐� true:�ݒ肳��Ă���,false:�ݒ肳��Ă��Ȃ�
	inline bool isSetTarget() {
		if (myTarget != nullptr)return true;
		return false;
	}

	inline std::shared_ptr<Object>GetMyTarget() {
		return myTarget;
	}

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

	//�K������x�N�g��
	const tnl::Vector3 FRONT = { 0,-1,0 };

	//---------------------------------------------------//

	//---------------�ˌ��֌W---------------------------//
	//�e���ˊԊu
	const float SHOOTCOOLDOWN = 0.1f;
	//�e���˃^�C�}�[
	float shootTimer = 0.0f;

	//Missile�N�[���_�E��
	const float MISSILECOOLDOWN = 1.0f;

	//Missile���˃^�C�}�[
	float missileTimer = 0.0f;

	//�e���˃|�C���g�␳
	const float INITPOSY = 25.0f;

	//�e�̑��x
	const float BULLETSPEED = 5.0f;

	//�I�[�g�^�[�Q�b�g�p
	std::shared_ptr<Object> myTarget = nullptr;

	//�I�[�g�^�[�Q�b�g���[�h
	bool autoTargetMode = false;

	//�q�s�X�s�[�h �X�e�[�W�����S�[���֌������X�s�[�h
	float CruizeSpeed = 0;

	//---------------�׏d�֌W---------------------------//
	//�׏d�ő�� �׏d�ʂ�����𒴂���ƍq�s�X�s�[�h�Ƀy�i���e�B���t��
	float maxCapacity = 0;
	//�׏d�� �^�ԉו��̑��d�� 
	float haveCapacity = 0;

	//--------------------------------------------------//
	
	//-----------------�摜�֌W---------------//
	//�I�[�g�^�[�Q�b�g�W��gh
	int targetingCircle = 0;

	//obj�t�@�N�g���[�|�C���^
	Factory* fac = nullptr;
};

