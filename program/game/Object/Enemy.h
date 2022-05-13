#pragma once
#include"Object.h"


class Enemy :public Object
{
public:
	Enemy(tnl::Vector3 StartPos);
	~Enemy();

	void Update()override;
	void Draw()override;
	void Init()override;
	void CheckIsLive()override;

private:

	void Move();

	enum class MOVETYPE {
		STRAIGHT,
		CHASE,
		MAX
	};


	//���x�x�N�g��
	tnl::Vector3 vecSpeed = {};
	//�ړ����@
	MOVETYPE type = MOVETYPE::STRAIGHT;
	//�ǔ�����Ȃ�
	bool isChase = false;

	//�X�e�[�^�X
	float hp = 0;
	float attack = 0;
	float shield = 0;

};

