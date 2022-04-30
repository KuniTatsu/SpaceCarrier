#pragma once
#include"Scene.h"
#include"GameManager.h"

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


};

