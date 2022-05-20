#pragma once
#include"../../dxlib_ext/dxlib_ext.h"
#include<memory>
class Factory;
class GameManager;

//移動方法のベースクラス
class ShootBase
{
public:
	ShootBase();
	virtual~ShootBase();
	//移動関数 仮想関数
	virtual bool Shoot(tnl::Vector3 Pos, int Radius, float Deltatime) = 0;
protected:

	Factory* fac = nullptr;
	GameManager* gManager = nullptr;

	//弾の進む速度ベクトル
	tnl::Vector3 vecSpeed = {};
	//次の発射までの必要クールダウン
	float COOLTIME = 0;
	//弾を撃つクールダウンタイム
	float coolDown = 0.0f;
};
//vecspeed方向ベクトルへ直進するクラス
class StraightShoot :public ShootBase
{
public:
	StraightShoot(tnl::Vector3 VecSpeed,float CoolDawn);
	~StraightShoot();

	bool Shoot(tnl::Vector3 Pos,int Radius,float Deltatime);
};

class FocusShoot :public ShootBase
{
public:
	FocusShoot(tnl::Vector3 VecSpeed, float CoolDawn);
	~FocusShoot();

	bool Shoot(tnl::Vector3 Pos, int Radius, float Deltatime);
};


