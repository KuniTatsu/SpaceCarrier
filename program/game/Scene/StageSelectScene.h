#pragma once
#include"Scene.h"
#include<vector>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class UIManager;
class Player;

class StageSelectScene:public BaseScene
{
public:
	StageSelectScene();
	~StageSelectScene();

	void Update();
	void Draw();

private:
	void Init();

	GameManager* gManager = nullptr;	
	UIManager* uiManager = nullptr;	

	//UI�摜�̊�_
	const tnl::Vector3 UIBASEPOS = { 200,200,0 };
	//UI�摜���m�̋���
	const int DISTANCE = 20;

	//UI�̘g�̕�
	const int UIWIDTH = 200;
	//UI�̘g�̍���
	const int UIHEIGHT = 200;

	//���肵���v�f�ԍ�
	int selectNum = -1;

	//�v�f�ԍ��ɑΉ�����X�e�[�W���쐬���V�[���J�ڂ���֐�
	void CreateStage();
	//�V�[���J�ڊm�F�ϐ�


	std::shared_ptr<Player>player = nullptr;
	
};
