#include "InGameScene.h"

InGameScene::InGameScene()
{
	Init();
}

InGameScene::~InGameScene()
{
}

void InGameScene::Update()
{

}

void InGameScene::Draw()
{
	/*if (gManager->GetList().empty())return;

	for (auto obj : gManager->GetList()) {
		obj->render(gManager->deitatime_);
	}*/
}

void InGameScene::Init()
{
	gManager = GameManager::Instance();
}
