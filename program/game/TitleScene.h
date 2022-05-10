#pragma once
#include"Scene.h"

class GameManager;

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


};