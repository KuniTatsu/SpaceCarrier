#include "TitleScene.h"
#include"GameManager.h"
#include"SceneManager.h"
//#include"Object.h"

TitleScene::TitleScene()
{
	gManager = GameManager::Instance();
	testGh = gManager->LoadGraphEx("graphics/test_1.png");
	backGroundGh = gManager->LoadGraphEx("graphics/backGround_1.jpg");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	/*gManager->Move();
	gManager->PlayerMove();*/
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) {
		SceneManager::ChangeScene(SceneManager::SCENE::INGAME);
		return;
	}

}

void TitleScene::Draw()
{
	/*if (gManager->GetList().empty())return;

	for (auto obj : gManager->GetList()) {
		obj->render(gManager->deitatime_);
	}*/

	DrawRotaGraph(512, 384, 1, 0, backGroundGh, false);
}
