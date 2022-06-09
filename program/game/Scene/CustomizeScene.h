//�D������������ו���ύڂ����肷��V�[��

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
	//player�̃C���X�^���X
	std::shared_ptr<Player>player = nullptr;
	//GameManager�̃C���X�^���X
	GameManager* gManager = nullptr;

	
	//�������֐�
	void Init();

};

