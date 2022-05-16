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
	if (GetRand(100) % 100 > 98) {
		auto enemy = std::dynamic_pointer_cast<Enemy, Object>(fac->create("Enemy", gManager->GetRandomPos(), tnl::Vector3(0, 5, 0), Factory::MOVETYPE::STRAIGHT));
		enemy->SetList();
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
	
	

	//tnl::IsIntersectSphere()

	//インスタンス消去
	bManager->RemoveBulletList();
	eManager->RemoveEnemyList();
	gManager->RemoveObjectList();
}

void InGameScene::Draw()
{
	DrawRotaGraph(512, 384, 1, 0, backGroundGh, false);

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
	//objectList = gManager->GetObjectList();
	player = gManager->GetPlayer();

	fac = gManager->GetFactory();
}
