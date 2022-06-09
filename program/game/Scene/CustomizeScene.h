//船を改造したり荷物を積載したりするシーン

#pragma once
#include"Scene.h"
#include"../Manager/GameManager.h"
#include<memory>

class Player;

class CustomizeScene :public BaseScene
{
public:
	CustomizeScene();
	~CustomizeScene();

	void Update();
	void Draw();

private:
	//playerのインスタンス
	std::shared_ptr<Player>player = nullptr;
	//GameManagerのインスタンス
	GameManager* gManager = nullptr;

	
	//初期化関数
	void Init();

};

