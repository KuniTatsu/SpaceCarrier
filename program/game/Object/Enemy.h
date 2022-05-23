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

	Enemy(tnl::Vector3 StartPos, std::string Gh, MovementBase* MoveType, ShootBase* ShootType);
	//特殊射撃を持たないEnemy
	Enemy(tnl::Vector3 StartPos, std::string Gh, float Hp, float Attack, float Defence, float Speed, MovementBase* MoveType, ShootBase* ShootType);
	//特殊射撃を持つEnemy
	Enemy(tnl::Vector3 StartPos, std::string Gh, float Hp, float Attack, float Defence, float Speed, MovementBase* MoveType, ShootBase* ShootType, ShootBase* ExShootType);

	~Enemy();

	void Update()override;
	void Draw()override;
	void Init()override;
	void CheckIsLive()override;
	//リスト登録
	void SetEnemyList();
	//行動パターン取得
	inline MovementBase* GetMovementType() {
		return moveType;
	}
	//射撃パターン取得
	inline ShootBase* GetShootType() {
		return shootType;
	}

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
	
	//ストラテジーパターンを使って行動を変えてみる
	//動き方
	MovementBase* moveType = nullptr;
	//射撃方法
	ShootBase* shootType = nullptr;
	//特殊射撃方法
	ShootBase* exShootType = nullptr;

	//ステータス
	float hp = 0;
	float attack = 0;
	float defence = 0;
	float speed = 0;

};

