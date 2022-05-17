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

	if (GetRand(100) % 100 > 98) {
		auto enemy = std::dynamic_pointer_cast<Enemy, Object>(fac->create("Enemy", gManager->GetRandomPos(), tnl::Vector3(0, 5, 0), Factory::MOVETYPE::STRAIGHT));
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


}

void InGameScene::Init()
{
	gManager = GameManager::Instance();
	bManager = BulletManager::Instance();
	eManager = EnemyManager::Instance();

	backGroundGh = gManager->LoadGraphEx("graphics/space.jpg");
	testGh = gManager->LoadGraphEx("graphics/space.jpg");

	backGroundPos = { gManager->Center.x,gManager->Center.y,0 };
	//objectList = gManager->GetObjectList();
	player = gManager->GetPlayer();

	fac = gManager->GetFactory();
}

void InGameScene::MoveBackGround()
{
	backGroundPos.y+=5;
	//画面下端に画像の上端が移動したら
	if (backGroundPos.y - 480 >= 768) {
		//元に戻す 元画像サイズと画面サイズの差を引く
		backGroundPos.y = gManager->Center.y-72;
	}
}
