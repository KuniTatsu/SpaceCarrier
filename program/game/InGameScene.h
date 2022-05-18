#pragma once
#include"Scene.h"
#include<memory>
#include<list>
#include"../dxlib_ext/dxlib_ext.h"

class GameManager;
class BulletManager;
class EnemyManager;
class Object;
class Player;
class Enemy;
class Factory;

class InGameScene :public BaseScene
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
	EnemyManager* eManager = nullptr;


	//enemyリスト
	std::list<std::shared_ptr<Enemy>>enemyList;

	std::shared_ptr<Player>player = nullptr;

	//objファクトリーポインタ
	Factory* fac = nullptr;

	//移動レーンの種類
	enum class LANE {
		NORMALSPEED,//移動速度*1.0 敵の強さも標準
		CRUISESPEED,//移動速度*1.5 敵の強さ*1.5
		HYPERSPEED,//移動速度*2.0  敵の強さ*2.0
		MAX
	};
	//現在の選択レーン
	LANE myLane = LANE::NORMALSPEED;

	const float LANEEXRATIO[static_cast<int>(LANE::MAX)]{ 1.0,1.5,2.0 };

	//ステージの長さ
	float stageLength = 0.0f;

	//ステージの現在地
	float nowStayPos = 0.0f;

	//ステージ進行度
	double progress = 0;

	//ステージ内の巡航関数 スタートからゴールに移動する関数
	void Cruize();


	//-------------背景関係---------------//

	//グラフィックハンドル
	int backGroundGh = 0;

	//test
	int testGh = 0;
	//背景の描画座標中心
	tnl::Vector3 backGroundPos = {};
	//背景画像の大きさ
	const int SIZEY = 960;

	//背景画像スクロール
	void MoveBackGround();

	//------------------------------------//

	//-------------UI関係---------------//
	//ステージ進行ゲージの元画像
	int stageGaugeBase = 0;
	//ステージ進行ゲージのFill画像
	int stageGaugeFill = 0;

	//進行ゲージの描画
	void DrawProgressGauge();
	//------------------------------------//

	//オブジェクトリスト
	//std::list<std::shared_ptr<Object>> objectList;

};

