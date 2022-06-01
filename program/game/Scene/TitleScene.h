#pragma once
#include"Scene.h"
#include<memory>

class GameManager;

class Ship;
class Inventory;
class GraphicUI;
class PartsManager;

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

	//-----------------------debugtest--------------------------------------//
	//Ship* testShip = nullptr;
	Inventory* testInventory = nullptr;

	bool init = false;

	int guideX = 100;
	int guideY = 50;


	int backWidth = 0;
	int backHeight = 0;

	std::shared_ptr<GraphicUI>back;

	PartsManager* pManager = nullptr;
	//-----------------------debugtest--------------------------------------//
};