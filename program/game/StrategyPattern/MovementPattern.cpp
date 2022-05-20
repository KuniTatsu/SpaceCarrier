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

//---------------直進移動Class-------------------//
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

//---------------遠距離停止Class-------------------//
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
	//上から来た敵が停止座標よりY座標が下なら移動しない
	if (Pos.y > stopPosY)return Pos;
	return tnl::Vector3();
}

//------------------------------------------------//

//---------------指定座標停止Class-------------------//
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
	//目的地についていたら移動しない
	if (stopPos.x == Pos.x && stopPos.y == Pos.y)return Pos;

	//目的地までの方向ベクトルを取得
	tnl::Vector3 moveVec = stopPos - Pos;
	//正規化
	tnl::Vector3 fixVec = gManager->GetFixVector(moveVec.x, moveVec.y);
	//速度をかけて移動
	return Pos += tnl::Vector3(fixVec.x * moveSpeed, fixVec.y * moveSpeed, 0);
}
//---------------------------------------------------//