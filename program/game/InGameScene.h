#pragma once
#include"Scene.h"
#include<memory>
#include<list>

class GameManager;
class BulletManager;
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
	
	//enemyリスト
	std::list<std::shared_ptr<Enemy>>enemyList;

	std::shared_ptr<Player>player = nullptr;

	//objファクトリーポインタ
	Factory* fac = nullptr;


	int backGroundGh = 0;
	//オブジェクトリスト
	//std::list<std::shared_ptr<Object>> objectList;

};

