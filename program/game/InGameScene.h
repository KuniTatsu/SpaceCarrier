#pragma once
#include"Scene.h"
#include<memory>
#include<list>

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

	
	//enemy���X�g
	std::list<std::shared_ptr<Enemy>>enemyList;

	std::shared_ptr<Player>player = nullptr;

	//obj�t�@�N�g���[�|�C���^
	Factory* fac = nullptr;


	int backGroundGh = 0;
	//�I�u�W�F�N�g���X�g
	//std::list<std::shared_ptr<Object>> objectList;

};

