#include "MovementPattern.h"
#include"../Manager/GameManager.h"

//---------------BaseClass-------------------//
MovementBase::MovementBase()
{
	gManager = GameManager::Instance();
}

MovementBase::~MovementBase()
{
}
//------------------------------------------//

//---------------���i�ړ�Class-------------------//
StraightMove::StraightMove(tnl::Vector3 VecSpeed)
{
	vecSpeed = VecSpeed;
}

StraightMove::~StraightMove()
{
}

tnl::Vector3 StraightMove::Move(tnl::Vector3 pos)
{
	return pos + vecSpeed;
}
//-----------------------------------------------//

//---------------��������~Class-------------------//
FarStopMove::FarStopMove(tnl::Vector3 VecSpeed, float StopPosY)
{
	vecSpeed = VecSpeed;
	stopPosY = StopPosY;
}

FarStopMove::~FarStopMove()
{
}

tnl::Vector3 FarStopMove::Move(tnl::Vector3 Pos)
{
	//�ォ�痈���G����~���W���Y���W�����Ȃ�ړ����Ȃ�
	if (Pos.y > stopPosY)return Pos;
	return Pos += vecSpeed;
}

//------------------------------------------------//

//---------------�w����W��~Class-------------------//
CenterStopMove::CenterStopMove(float Speed, tnl::Vector3 StopPos)
{
	moveSpeed = Speed;
	stopPos = StopPos;
}

CenterStopMove::~CenterStopMove()
{
}

tnl::Vector3 CenterStopMove::Move(tnl::Vector3 Pos)
{
	////�ړI�n�ɂ��Ă�����ړ����Ȃ�
	//if (stopPos.x == Pos.x && stopPos.y == Pos.y)return Pos;

	//�ړI�n�܂ł̕����x�N�g�����擾
	tnl::Vector3 moveVec = stopPos - Pos;

	//�����x�N�g���̑傫�����擾
	float vecLength = std::sqrt(moveVec.x * moveVec.x + moveVec.y * moveVec.y);

	//�����x�N�g���̑傫��=���������ȉ��Ȃ�ړ����Ȃ�
	if (vecLength < 1.0f)return Pos;

	//���K��
	tnl::Vector3 fixVec = gManager->GetFixVector(moveVec.x, moveVec.y);
	//���x�������Ĉړ�
	return Pos += tnl::Vector3(fixVec.x * moveSpeed, fixVec.y * moveSpeed, 0);
}
//---------------------------------------------------//

//---------------�����ړ�Class-------------------//
AccelMove::AccelMove(tnl::Vector3 VecSpeed, float StartSpeed, float Accel, float MaxSpeed)
{
	vecSpeed = VecSpeed;
	moveSpeed = StartSpeed;

	accel = Accel;
	maxMoveSpeed = MaxSpeed;
}

AccelMove::~AccelMove()
{
}

tnl::Vector3 AccelMove::Move(tnl::Vector3 Pos)
{
	//�ő呬�x�ȉ��Ȃ����������
	if (moveSpeed < maxMoveSpeed) moveSpeed += accel;

	return Pos += (vecSpeed * moveSpeed);
}

SlideMove::SlideMove(tnl::Vector3 VecSpeed)
{
	vecSpeed = VecSpeed;
}

SlideMove::~SlideMove()
{
}

tnl::Vector3 SlideMove::Move(tnl::Vector3 Pos)
{
	return Pos += vecSpeed;
}