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

	//UI画像の基準点
	const tnl::Vector3 UIBASEPOS = { 200,200,0 };
	//UI画像同士の距離
	const int DISTANCE = 20;

	//UIの枠の幅
	const int UIWIDTH = 200;
	//UIの枠の高さ
	const int UIHEIGHT = 200;

	//決定した要素番号
	int selectNum = -1;

	//要素番号に対応するステージを作成しシーン遷移する関数
	void CreateStage();
	//シーン遷移確認変数


	std::shared_ptr<Player>player = nullptr;
	
};
