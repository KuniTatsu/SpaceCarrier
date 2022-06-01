#pragma once
#include"Scene.h"

class GameManager;

class Ship;
class Inventory;

class TitleScene:public BaseScene 
{

public:
	TitleScene();
	~TitleScene();

	void Update();
	void Draw();

private:
	GameManager* gManager = nullptr;

	int testGh = 0;

	int backGroundGh = 0;

	//Ship* testShip = nullptr;
	Inventory* testInventory = nullptr;

	bool init = false;

	int guideX = 100;
	int guideY = 50;

};