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

	
	//enemy���X�g
	std::list<std::shared_ptr<Enemy>>enemyList;

	std::shared_ptr<Player>player = nullptr;

	//obj�t�@�N�g���[�|�C���^
	Factory* fac = nullptr;

	//�O���t�B�b�N�n���h��
	int backGroundGh = 0;

	//test
	int testGh = 0;
	//�w�i�̕`����W���S
	tnl::Vector3 backGroundPos = {};
	//�w�i�摜�̑傫��
	const int SIZEY = 960;

	//�w�i�摜�X�N���[��
	void MoveBackGround();


	//�I�u�W�F�N�g���X�g
	//std::list<std::shared_ptr<Object>> objectList;

};

