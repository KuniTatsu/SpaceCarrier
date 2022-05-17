#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

//�ړ����@�̃x�[�X�N���X
class MovementBase
{
public:
	MovementBase();
	~MovementBase();
	//�ړ��֐� ���z�֐�
	virtual tnl::Vector3 Move(tnl::Vector3 Pos) = 0;
protected:

	tnl::Vector3 vecSpeed = {};
};
//vecspeed�����x�N�g���֒��i����N���X
class StraightMove:public MovementBase
{
public:
	StraightMove(tnl::Vector3 VecSpeed);
	~StraightMove();

	tnl::Vector3 Move(tnl::Vector3 Pos);
};


