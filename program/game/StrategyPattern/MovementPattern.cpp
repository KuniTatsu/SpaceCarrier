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
	return Pos += vecSpeed;
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
	////目的地についていたら移動しない
	//if (stopPos.x == Pos.x && stopPos.y == Pos.y)return Pos;

	//目的地までの方向ベクトルを取得
	tnl::Vector3 moveVec = stopPos - Pos;

	//方向ベクトルの大きさを取得
	float vecLength = std::sqrt(moveVec.x * moveVec.x + moveVec.y * moveVec.y);

	//方向ベクトルの大きさ=距離が一定以下なら移動しない
	if (vecLength < 1.0f)return Pos;

	//正規化
	tnl::Vector3 fixVec = gManager->GetFixVector(moveVec.x, moveVec.y);
	//速度をかけて移動
	return Pos += tnl::Vector3(fixVec.x * moveSpeed, fixVec.y * moveSpeed, 0);
}
//---------------------------------------------------//

//---------------加速移動Class-------------------//
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
	//最大速度以下なら加速させる
	if (moveSpeed < maxMoveSpeed) moveSpeed += accel;

	return Pos += (vecSpeed * moveSpeed);
}
//---------------スライド移動Class-------------------//
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

//---------------追尾移動Class-------------------//
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

	//弾からみてターゲットの位置が右か左かを求める
	//ターゲットへの方向ベクトル
	tnl::Vector3 dirVec = target->GetPos() - Pos;

	//vecSpeedとdirVecの外積を取得
	float crossVec = gManager->GetCross(vecSpeed, dirVec);

	//crossVecが0以上なら左,以下なら右に回転させる
	if (crossVec < 0) {
		float fixVecX = vecSpeed.x * radianX + vecSpeed.y * radianY;
		float fixVecY = vecSpeed.x * (-1) * radianY + vecSpeed.y * radianX;
		//回転させた速度ベクトルをvecSpeedに代入
		vecSpeed.x = fixVecX;
		vecSpeed.y = fixVecY;
	}
	else
	{
		float fixVecX = vecSpeed.x * radianX - vecSpeed.y * radianY;
		float fixVecY = vecSpeed.x * radianY + vecSpeed.y * radianX;
		//回転させた速度ベクトルをvecSpeedに代入
		vecSpeed.x = fixVecX;
		vecSpeed.y = fixVecY;
	}
	return Pos + vecSpeed;
	/*

	//一フレームの回転角は1.0とする
	//反時計回り
	x' = x * cos - y * sin
	y' = x * sin + y * cos

	//時計回り
	x'=x*cos+y*sin
	y'=x*-sin+y*cos

	*/
}
