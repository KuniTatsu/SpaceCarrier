#pragma once
#include"Object.h"


class GameManager;
class BulletManager;
class MovementBase;

class Bullet :public Object
{
public:
	Bullet() {};
	Bullet(tnl::Vector3& StartPos, tnl::Vector3& VPos);

	Bullet(tnl::Vector3 StartPos,MovementBase* MoveType);

	~Bullet();

	void Update()override;
	void Draw()override;
	void Init()override;
	//非推奨
	void Initialize(tnl::Vector3& StartPos, tnl::Vector3& VPos);
	//推奨
	void Initialize(tnl::Vector3& StartPos);

	void CheckIsLive()override;

	//PlayerBulletリスト登録
	void SetBulletList();

	//EnemyBulletリスト登録
	void SetEnemyBulletList();

private:
	//BulletManagerのインスタンス
	BulletManager* bManager = nullptr;


	//移動ベクトル
	tnl::Vector3 vPos = {};

	//最大生存時間
	const float MAXLIVETIME = 10.0f;

	//生存時間
	float liveTime = 0.0f;

	//ストラテジーパターンを使って行動を変えてみる
	MovementBase* moveType = nullptr;


};

