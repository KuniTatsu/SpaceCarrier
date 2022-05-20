#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;

//�ړ����@�̃x�[�X�N���X
class MovementBase
{
public:
	MovementBase();
	virtual ~MovementBase();
	//�ړ��֐� ���z�֐�
	virtual tnl::Vector3 Move(tnl::Vector3 Pos) = 0;
protected:
	//���x�x�N�g��
	tnl::Vector3 vecSpeed = {};
	//gameManagerpoint
	GameManager* gManager = nullptr;
};
//vecspeed�����x�N�g���֒��i����N���X
class StraightMove :public MovementBase
{
public:
	StraightMove(tnl::Vector3 VecSpeed);
	~StraightMove();

	tnl::Vector3 Move(tnl::Vector3 Pos)override;
};
//��ʏ㕔�Ŏ~�܂�N���X �G���ォ�痈�邱�ƑO��
class FarStopMove :public MovementBase 
{
public:
	FarStopMove(tnl::Vector3 VecSpeed,float StopPosY);
	~FarStopMove();

	tnl::Vector3 Move(tnl::Vector3 Pos)override;

	inline float GetStopPosY() {
		return stopPosY;
	}
private:
	float stopPosY = 0;
};
//������W�Ŏ~�܂�N���X �ʏ�͉�ʒ��S
class CenterStopMove :public MovementBase
{
public:
	CenterStopMove(float Speed, tnl::Vector3 StopPos);
	~CenterStopMove();
	//�w����W���猻�ݍ��W�������ĕ����x�N�g�����o��
	//�o���������x�N�g���𐳋K������
	//���K���x�N�g���ɑ��x�������Ĉړ�����
	tnl::Vector3 Move(tnl::Vector3 Pos)override;

	inline tnl::Vector3& GetStopPos() {
		return stopPos;
	}
private:
	//�ڕW��~���W�Ɍ������X�s�[�h
	float moveSpeed = 0;
	//�ڕW��~���W
	tnl::Vector3 stopPos = {};
};
