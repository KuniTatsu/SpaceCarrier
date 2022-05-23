#pragma once
#include"Scene.h"
#include<memory>
#include<list>
#include<vector>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class BulletManager;
class EnemyManager;
class Object;
class Player;
class Enemy;
class Factory;
class Animation;

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

	//--------------シークエンス関係----------------//
	tnl::Sequence<InGameScene>mainSeqence =
		tnl::Sequence<InGameScene>(this, &InGameScene::SeqCruize);

	//巡航シークエンス
	bool SeqCruize(const float deltatime);
	//ゴール後リザルトシークエンス
	bool SeqGoalResalt(const float deltatime);



	//シークエンスの列挙体
	enum class sequence {
		CRUIZE,
		GOALRESALT,
		MAX

	};
	sequence nowSeq = sequence::CRUIZE;
	sequence lastSeq = sequence::CRUIZE;

	//Sequenceを移動させる関数,enumも一緒に変更する
	void ChangeSequence(const sequence seq);
	//----------------------------------------------//

	//--------------ステージ進捗関係----------------//

	//移動レーンの種類
	enum class LANE {
		NORMALSPEED,//移動速度*1.0 敵の強さも標準
		CRUISESPEED,//移動速度*1.5 敵の強さ*1.5
		HYPERSPEED,//移動速度*2.0  敵の強さ*2.0
		MAX
	};
	//現在の選択レーン
	LANE myLane = LANE::NORMALSPEED;
	//レーンごとの巡航速度レート
	const float LANEEXRATIO[static_cast<int>(LANE::MAX)]{ 1.0,1.5,2.0 };

	//プレイヤーの巡航速度を取得
	float PlayerSpeed = 0.0f;
	//荷重率の取得
	float CapacityRate = 0.0f;

	//ステージの長さ
	float stageLength = 0.0f;

	//ステージの現在地
	float nowStayPos = 0.0f;

	//ステージ進行度
	double progress = 0;

	//ステージ内の巡航関数 スタートからゴールに移動する関数
	bool Cruize();

	//ステージの進捗状況のリセット
	void ResetStageProgress();

	//------------------------------------//
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

	//ゴール画像
	int goalTestGh = 0;

	//進行ゲージの描画
	void DrawProgressGauge();
	//------------------------------------//

	//-------------エフェクト関係------------//
	//画面内に生きているエフェクトリスト
	std::list<std::shared_ptr<Animation>>liveAnimationList;

	//アニメーション生成
	void MakeAnimation(std::string Gh, tnl::Vector3 Pos, int ActSpeed, int MaxIndex, int XNum, int YNum, int XSize, int YSize);
	//アニメーション更新
	void UpdateAnimation();
	//アニメーション描画
	void DrawAnimation();
	//アニメーション破棄
	void DeleteAnimation();

	//---------------------------------------//

	//すべての敵の中から一番playerに近い敵を選ぶ関数
	std::shared_ptr<Enemy>GetNearestEnemy();

	//敵を倒したフラグ
	bool isDestroyEnemy = false;

	//オブジェクトリスト
	//std::list<std::shared_ptr<Object>> objectList;

};

