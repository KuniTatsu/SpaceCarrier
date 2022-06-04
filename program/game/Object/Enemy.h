#pragma once
#include"Object.h"

class MovementBase;
class ShootBase;
class GameManager;
class EnemyManager;
class Observer;

class Enemy :public Object
{
public:
	explicit Enemy(tnl::Vector3 StartPos);

	Enemy(tnl::Vector3 StartPos, std::string Gh, MovementBase* MoveType, ShootBase* ShootType);
	//����ˌ��������Ȃ�Enemy
	Enemy(tnl::Vector3 StartPos, std::string Gh, float Hp, float Attack, float Defence, float Speed, MovementBase* MoveType, ShootBase* ShootType);
	//����ˌ�������Enemy
	Enemy(tnl::Vector3 StartPos, std::string Gh, float Hp, float Attack, float Defence, float Speed, MovementBase* MoveType, ShootBase* ShootType, ShootBase* ExShootType);

	~Enemy();

	void Update()override;
	void Draw()override;
	void Init()override;
	void CheckIsLive()override;
	//���X�g�o�^
	void SetEnemyList();
	//�s���p�^�[���擾
	inline MovementBase* GetMovementType() {
		return moveType;
	}
	//�ˌ��p�^�[���擾
	inline ShootBase* GetShootType() {
		return shootType;
	}

	//�ω�������I�u�U�[�o�̊֐����Ă�
	void notify();

protected:
	//�G�l�~�[�}�l�[�W���|�C���^
	EnemyManager* eManager = nullptr;

	//�I�u�U�[�o
	Observer* enemyChecker = nullptr;

	//�I�u�U�[�o�o�^�֐�
	void SetObserver(Observer* EnemyChecker);

	//�I�u�U�[�o�����֐�
	inline void CleanObserver() {
		enemyChecker = nullptr;
	}
	

	//Movetype�œ����֐�
	void Move();

	/*enum class MOVETYPE {
		STRAIGHT,
		CHASE,
		MAX
	};*/
	/*
	//�ړ����@
	MOVETYPE type = MOVETYPE::STRAIGHT;
	//�ǔ�����Ȃ�
	bool isChase = false;
	*/
	
	//�X�g���e�W�[�p�^�[�����g���čs����ς��Ă݂�
	//������
	MovementBase* moveType = nullptr;
	//�ˌ����@
	ShootBase* shootType = nullptr;
	//����ˌ����@
	ShootBase* exShootType = nullptr;

	//���������
	void DeleteMemory();

	//�X�e�[�^�X
	float hp = 0;
	float attack = 0;
	float defence = 0;
	float speed = 0;

};

