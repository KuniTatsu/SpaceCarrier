#pragma once
#include"Scene.h"
#include<memory>
#include<list>
#include"../dxlib_ext/dxlib_ext.h"

class GameManager;
class BulletManager;
class EnemyManager;
class Object;
class Player;
class Enemy;
class Factory;

class InGameScene:public BaseScene
{
public:
	InGameScene();
	~InGameScene();

	void Update();
	void Draw();

private:

	void Init();
	GameManager* gManager = nullptr;
	BulletManager* bManager = nullptr;
	EnemyManager* eManager = nullptr;

	
	//enemyリスト
	std::list<std::shared_ptr<Enemy>>enemyList;

	std::shared_ptr<Player>player = nullptr;

	//objファクトリーポインタ
	Factory* fac = nullptr;

	//グラフィックハンドル
	int backGroundGh = 0;

	//test
	int testGh = 0;
	//背景の描画座標中心
	tnl::Vector3 backGroundPos = {};
	//背景画像の大きさ
	const int SIZEY = 960;

	//背景画像スクロール
	void MoveBackGround();


	//オブジェクトリスト
	//std::list<std::shared_ptr<Object>> objectList;

};

