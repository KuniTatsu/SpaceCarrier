#include "InGameScene.h"
#include"Manager/BulletManager.h"
#include"Manager/EnemyManager.h"
#include"Object/Bullet.h"
#include"GameManager.h"
#include"Object/Object.h"
#include"Object/Player.h"
#include"Factory.h"
#include<time.h>
#include"Object/Enemy.h"

InGameScene::InGameScene()
{
	Init();
}

InGameScene::~InGameScene()
{
}

void InGameScene::Update()
{
	//背景移動
	MoveBackGround();
	//ステージ進捗更新
	Cruize();

	if (GetRand(100) % 100 > 98) {
		auto enemy = std::dynamic_pointer_cast<Enemy, Object>(fac->create("Enemy", gManager->GetRandomPos(),
			tnl::Vector3(0, 2, 0), Factory::MOVETYPE::STRAIGHT, Factory::SHOOTTYPE::STRAIGHT));
		enemy->SetList();
		enemy->SetEnemyList();
	}


	//spaceキーを押したら弾を発射する
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_SPACE))player->ShootBullet();

	//オブジェクトリストのアップデート
	{
		auto list = gManager->GetObjectList();
		auto it = list.begin();

		while (it != list.end()) {
			(*it)->Update();
			it++;
		}
	}
	//弾とエネミーの当たり判定
	for (auto enemy : eManager->GetList()) {
		for (auto bullet : bManager->GetList()) {
			if (tnl::IsIntersectSphere(enemy->GetPos(), enemy->GetRadius(), bullet->GetPos(), bullet->GetRadius())) {
				enemy->SetIsLive();
				bullet->SetIsLive();
			}
		}
	}

	//tnl::IsIntersectSphere()

	//インスタンス消去
	bManager->RemoveBulletList();
	eManager->RemoveEnemyList();
	gManager->RemoveObjectList();
}

void InGameScene::Draw()
{
	//一枚目の背景画像
	DrawRotaGraph(backGroundPos.x, backGroundPos.y, 2, 0, backGroundGh, false);
	DrawRotaGraph(backGroundPos.x, backGroundPos.y - SIZEY, 2, 0, testGh, false);

	auto objectList = gManager->GetObjectList();
	auto itr = objectList.begin();

	for (int i = 0; i < objectList.size(); ++i) {
		(*itr)->Draw();
		++itr;
	}

	DrawProgressGauge();
}

void InGameScene::Init()
{
	gManager = GameManager::Instance();
	bManager = BulletManager::Instance();
	eManager = EnemyManager::Instance();

	backGroundGh = gManager->LoadGraphEx("graphics/space.jpg");
	testGh = gManager->LoadGraphEx("graphics/space.jpg");

	stageGaugeBase = gManager->LoadGraphEx("graphics/StageGauge_None.png");
	stageGaugeFill = gManager->LoadGraphEx("graphics/StageGauge_Fill.png");

	backGroundPos = { gManager->Center.x,gManager->Center.y,0 };
	//objectList = gManager->GetObjectList();
	player = gManager->GetPlayer();

	fac = gManager->GetFactory();

	stageLength = gManager->GetStageLength();


}

void InGameScene::MoveBackGround()
{
	backGroundPos.y += 5;
	//画面下端に画像の上端が移動したら
	if (backGroundPos.y - 480 >= 768) {
		//元に戻す 元画像サイズと画面サイズの差を引く
		backGroundPos.y = gManager->Center.y - 72;
	}
}

void InGameScene::Cruize()
{
	//プレイヤーの巡航速度を取得
	const float PLAYERSPEED = player->GetCruizeSpeed();
	//荷重率の取得
	const float CAPACITYRATE = player->GetCapaciryRate();

	//一秒で進む距離を取得 巡航速度と荷重率,レーン補正をかけた値を乗算
	//荷重率は逆数をかける(軽い(1未満)と早くなり、重い(1以上)と遅くなる)
	float addCruizeDistance = 0;
	//荷重率が0の場合は無視する
	if (CAPACITYRATE == 0) {
		addCruizeDistance = (PLAYERSPEED * LANEEXRATIO[static_cast<int>(myLane)]);
	}
	else {
		addCruizeDistance = (PLAYERSPEED * LANEEXRATIO[static_cast<int>(myLane)]) / CAPACITYRATE;
	}

	//progressが1になっていれば加算しない
	if (progress >= 1.0)return;
	//現在地に加算する
	nowStayPos += addCruizeDistance *gManager->deltatime;

	//debug
	//nowStayPos += addCruizeDistance *gManager->deltatime*3;

	//ステージの進捗率更新
	progress = static_cast<double>(nowStayPos / stageLength);
}

void InGameScene::DrawProgressGauge()
{
	//ステージ進行ゲージの描画5
	DrawRotaGraph(1024 - 25, gManager->Center.y, 1, 0, stageGaugeBase, true);
	//現在の進行度に応じてゲージの長さを描画
	DrawRotaGraph3(1024, 768-5, 50, 768, 1, progress, 0, stageGaugeFill, true);

	tnl::DebugTrace("\n%.2f\n", progress);
}
