#pragma once
#include"Scene.h"
#include<memory>
#include<list>

class GameManager;
class BulletManager;
class Object;
class Player;

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

	std::shared_ptr<Player>player = nullptr;


	int backGroundGh = 0;
	//�I�u�W�F�N�g���X�g
	//std::list<std::shared_ptr<Object>> objectList;

};

