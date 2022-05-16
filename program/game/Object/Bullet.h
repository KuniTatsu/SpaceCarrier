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

	//Bulletリスト登録
	void SetBulletList();


private:
	//BulletManagerのインスタンス
	BulletManager* bManager = nullptr;


	//移動ベクトル
	tnl::Vector3 vPos = {};

	//ストラテジーパターンを使って行動を変えてみる
	MovementBase* moveType = nullptr;


};

