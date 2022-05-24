#include "MovementPattern.h"
#include"../Manager/GameManager.h"
#include"../Object/Object.h"
#include<math.h>

//---------------BaseClass-------------------//
MovementBase::MovementBase()
{
	gManager = GameManager::Instance();
	radianX = cos(tnl::ToRadian(5.0f));
	radianY = sin(tnl::ToRadian(5.0f));
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
//---------------�X���C�h�ړ�Class-------------------//
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

//---------------�ǔ��ړ�Class-------------------//
ToTargetMove::ToTargetMove(tnl::Vector3 VecSpeed, std::shared_ptr<Object> Target)
{
	target = Target;
	vecSpeed = VecSpeed;
}

ToTargetMove::~ToTargetMove()
{
}

tnl::Vector3 ToTargetMove::Move(tnl::Vector3 Pos)
{

	//�e����݂ă^�[�Q�b�g�̈ʒu���E�����������߂�
	//�^�[�Q�b�g�ւ̕����x�N�g��
	tnl::Vector3 dirVec = target->GetPos() - Pos;

	//vecSpeed��dirVec�̊O�ς��擾
	float crossVec = gManager->GetCross(vecSpeed, dirVec);

	//crossVec��0�ȏ�Ȃ獶,�ȉ��Ȃ�E�ɉ�]������
	if (crossVec < 0) {
		float fixVecX = vecSpeed.x * radianX + vecSpeed.y * radianY;
		float fixVecY = vecSpeed.x * (-1) * radianY + vecSpeed.y * radianX;
		//��]���������x�x�N�g����vecSpeed�ɑ��
		vecSpeed.x = fixVecX;
		vecSpeed.y = fixVecY;
	}
	else
	{
		float fixVecX = vecSpeed.x * radianX - vecSpeed.y * radianY;
		float fixVecY = vecSpeed.x * radianY + vecSpeed.y * radianX;
		//��]���������x�x�N�g����vecSpeed�ɑ��
		vecSpeed.x = fixVecX;
		vecSpeed.y = fixVecY;
	}
	return Pos + vecSpeed;
	/*

	//��t���[���̉�]�p��1.0�Ƃ���
	//�����v���
	x' = x * cos - y * sin
	y' = x * sin + y * cos

	//���v���
	x'=x*cos+y*sin
	y'=x*-sin+y*cos

	*/
}
