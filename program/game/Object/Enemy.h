#pragma once
#include"Object.h"

class MovementBase;
class ShootBase;
class GameManager;
class EnemyManager;

class Enemy :public Object
{
public:
	explicit Enemy(tnl::Vector3 StartPos);

	Enemy(tnl::Vector3 StartPos, MovementBase* MoveType, ShootBase* ShootType);
	~Enemy();

	void Update()override;
	void Draw()override;
	void Init()override;
	void CheckIsLive()override;

	void SetEnemyList();



protected:
	EnemyManager* eManager = nullptr;


	void Move();

	/*enum class MOVETYPE {
		STRAIGHT,
		CHASE,
		MAX
	};*/
	/*
	//移動方法
	MOVETYPE type = MOVETYPE::STRAIGHT;
	//追尾ありなし
	bool isChase = false;
	*/
	//速度ベクトル
	tnl::Vector3 vecSpeed = {};

	//ストラテジーパターンを使って行動を変えてみる
	MovementBase* moveType = nullptr;
	ShootBase* shootType = nullptr;


	//ステータス
	float hp = 0;
	float attack = 0;
	float shield = 0;

};

