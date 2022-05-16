#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

//移動方法のベースクラス
class MovementBase
{
public:
	MovementBase();
	~MovementBase();
	//移動関数 仮想関数
	virtual tnl::Vector3 Move(tnl::Vector3 Pos) = 0;
protected:

	tnl::Vector3 vecSpeed = {};
};
//vecspeed方向ベクトルへ直進するクラス
class StraightMove:public MovementBase
{
public:
	StraightMove(tnl::Vector3 VecSpeed);
	~StraightMove();

	tnl::Vector3 Move(tnl::Vector3 Pos);
};


