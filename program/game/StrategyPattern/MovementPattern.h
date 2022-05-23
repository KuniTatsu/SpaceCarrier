#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;

//移動方法のベースクラス
class MovementBase
{
public:
	MovementBase();
	virtual ~MovementBase();
	//移動関数 仮想関数
	virtual tnl::Vector3 Move(tnl::Vector3 Pos) = 0;

	//速度ベクトル取得関数
	inline tnl::Vector3 GetVecSpeed() {
		return vecSpeed;
	}

protected:
	//速度ベクトル
	tnl::Vector3 vecSpeed = {};
	//gameManagerpoint
	GameManager* gManager = nullptr;
};
//vecspeed方向ベクトルへ直進するクラス
class StraightMove :public MovementBase
{
public:
	StraightMove(tnl::Vector3 VecSpeed);
	~StraightMove();

	tnl::Vector3 Move(tnl::Vector3 Pos)override;
};
//画面上部で止まるクラス 敵が上から来ること前提
class FarStopMove :public MovementBase
{
public:
	FarStopMove(tnl::Vector3 VecSpeed, float StopPosY);
	~FarStopMove();

	tnl::Vector3 Move(tnl::Vector3 Pos)override;

	inline float GetStopPosY() {
		return stopPosY;
	}
private:
	float stopPosY = 0;
};
//特定座標で止まるクラス 通常は画面中心
class CenterStopMove :public MovementBase
{
public:
	CenterStopMove(float Speed, tnl::Vector3 StopPos);
	~CenterStopMove();
	//指定座標から現在座標を引いて方向ベクトルを出す
	//出した方向ベクトルを正規化する
	//正規化ベクトルに速度をかけて移動する
	tnl::Vector3 Move(tnl::Vector3 Pos)override;

	inline tnl::Vector3& GetStopPos() {
		return stopPos;
	}
private:
	//目標停止座標に向かうスピード
	float moveSpeed = 0;
	//目標停止座標
	tnl::Vector3 stopPos = {};
};

//だんだん早くなる直進移動クラス
class AccelMove :public MovementBase
{
public:
	//VecSpeed:速度ベクトル,StartSpeed:速度倍率,Accel:速度倍率の増え方,MaxSpeed:最大速度倍率
	AccelMove(tnl::Vector3 VecSpeed, float StartSpeed = 1.0f, float Accel = 0.01f, float MaxSpeed = 2.0f);
	~AccelMove();
	//指定座標から現在座標を引いて方向ベクトルを出す
	//出した方向ベクトルを正規化する
	//正規化ベクトルに速度をかけて移動する
	tnl::Vector3 Move(tnl::Vector3 Pos)override;


private:
	//移動スピード
	float moveSpeed = 0;

	//加速度
	float accel = 0;

	//最大移動スピード
	float maxMoveSpeed = 0;

};
//スライド移動するクラス
class SlideMove :public MovementBase
{
public:
	//速度ベクトルは左右方向
	SlideMove(tnl::Vector3 VecSpeed);
	~SlideMove();
	//指定座標から現在座標を引いて方向ベクトルを出す
	//出した方向ベクトルを正規化する
	//正規化ベクトルに速度をかけて移動する
	tnl::Vector3 Move(tnl::Vector3 Pos)override;
};
////Playerに向かうクラス---->いずれ無くす
//class ToPlayerMove :public MovementBase
//{
//public:
//	//速度ベクトルは左右方向
//	ToPlayerMove(tnl::Vector3 VecSpeed);
//	~ToPlayerMove();
//	//指定座標から現在座標を引いて方向ベクトルを出す
//	//出した方向ベクトルを正規化する
//	//正規化ベクトルに速度をかけて移動する
//	tnl::Vector3 Move(tnl::Vector3 Pos)override;
//};
