#include "InGameScene.h"
#include"Manager/BulletManager.h"
#include"Object/Bullet.h"
#include"GameManager.h"
#include"Object/Object.h"
#include"Object/Player.h"

InGameScene::InGameScene()
{
	Init();
}

InGameScene::~InGameScene()
{
}

void InGameScene::Update()
{
	//space�L�[����������e�𔭎˂���
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_SPACE))player->ShootBullet();

	//�I�u�W�F�N�g���X�g�̃A�b�v�f�[�g
	{
		auto list = gManager->GetObjectList();
		auto it = list.begin();

		while (it != list.end()) {
			(*it)->Update();
			it++;
		}
	}

	//�e�̃C���X�^���X����
	bManager->RemoveBulletList();
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
	

	backGroundGh = gManager->LoadGraphEx("graphics/space.jpg");
	//objectList = gManager->GetObjectList();
	player = gManager->GetPlayer();
}
