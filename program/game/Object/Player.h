#pragma once
#include"Object.h"
#include<memory>

class GameManager;

class Player final :public Object
{
public:
	Player();
	~Player();

	void Update()override;
	void Draw()override;
	void Init()override;
	

private:
	GameManager* gManager = nullptr;


};

