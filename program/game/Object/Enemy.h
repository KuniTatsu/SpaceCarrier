#pragma once
#include"Object.h"

class MovementBase;
class ShootBase;
class GameManager;
class EnemyManager;

class Enemy :public Object
{
public:
	explicit Enemy(tnl::Vector3 StartPos);

	Enemy(tnl::Vector3 StartPos, MovementBase* MoveType, ShootBase* ShootType);
	~Enemy();

	void Update()override;
	void Draw()override;
	void Init()override;
	void CheckIsLive()override;

	void SetEnemyList();



protected:
	EnemyManager* eManager = nullptr;


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
	//���x�x�N�g��
	tnl::Vector3 vecSpeed = {};

	//�X�g���e�W�[�p�^�[�����g���čs����ς��Ă݂�
	MovementBase* moveType = nullptr;
	ShootBase* shootType = nullptr;


	//�X�e�[�^�X
	float hp = 0;
	float attack = 0;
	float shield = 0;

};

