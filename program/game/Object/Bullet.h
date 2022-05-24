#pragma once
#include"Object.h"


class GameManager;
class BulletManager;
class MovementBase;

class Bullet :public Object
{
public:
	Bullet() {};
	Bullet(tnl::Vector3& StartPos, tnl::Vector3& VPos);

	Bullet(tnl::Vector3 StartPos,MovementBase* MoveType);

	~Bullet();

	void Update()override;
	void Draw()override;
	void Init()override;
	//�񐄏�
	void Initialize(tnl::Vector3& StartPos, tnl::Vector3& VPos);
	//����
	void Initialize(tnl::Vector3& StartPos);

	void CheckIsLive()override;

	//PlayerBullet���X�g�o�^
	void SetBulletList();

	//EnemyBullet���X�g�o�^
	void SetEnemyBulletList();

private:
	//BulletManager�̃C���X�^���X
	BulletManager* bManager = nullptr;


	//�ړ��x�N�g��
	tnl::Vector3 vPos = {};

	//�ő吶������
	const float MAXLIVETIME = 10.0f;

	//��������
	float liveTime = 0.0f;

	//�X�g���e�W�[�p�^�[�����g���čs����ς��Ă݂�
	MovementBase* moveType = nullptr;


};

