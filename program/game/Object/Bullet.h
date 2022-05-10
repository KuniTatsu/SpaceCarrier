#pragma once
#include"Object.h"


class GameManager;
class BulletManager;

class Bullet:public Object
{
public:
	Bullet() {};
	Bullet(tnl::Vector3& StartPos, tnl::Vector3& VPos);
	~Bullet();

	void Update()override;
	void Draw()override;
	void Init()override;

	void Initialize(tnl::Vector3& StartPos, tnl::Vector3& VPos);

	void CheckIsLive()override;


private:
	//BulletManagerのインスタンス
	BulletManager* bManager = nullptr;


	//移動ベクトル
	tnl::Vector3 vPos = {};


	

};

