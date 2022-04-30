#include "TitleScene.h"
#include"GameManager.h"
#include"Object.h"

TitleScene::TitleScene()
{
	gManager = GameManager::Instance();


}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	gManager->Move();
	gManager->PlayerMove();
}

void TitleScene::Draw()
{
	if (gManager->GetList().empty())return;

	for (auto obj : gManager->GetList()) {
		obj->render(gManager->deitatime_);
	}

}
