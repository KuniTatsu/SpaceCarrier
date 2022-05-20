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
	return tnl::Vector3();
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
	//�ړI�n�ɂ��Ă�����ړ����Ȃ�
	if (stopPos.x == Pos.x && stopPos.y == Pos.y)return Pos;

	//�ړI�n�܂ł̕����x�N�g�����擾
	tnl::Vector3 moveVec = stopPos - Pos;
	//���K��
	tnl::Vector3 fixVec = gManager->GetFixVector(moveVec.x, moveVec.y);
	//���x�������Ĉړ�
	return Pos += tnl::Vector3(fixVec.x * moveSpeed, fixVec.y * moveSpeed, 0);
}
//---------------------------------------------------//