#include "TitleScene.h"
#include"../Manager/GameManager.h"
#include"../Manager/SceneManager.h"
#include"../Ship.h"

//#include"Object.h"

TitleScene::TitleScene()
{
	gManager = GameManager::Instance();
	//testGh = gManager->LoadGraphEx("graphics/test_1.png");
	backGroundGh = gManager->LoadGraphEx("graphics/TestTitle.png");

	//testShip = new Ship();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{

	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
		return;
	}
	
}

void TitleScene::Draw()
{


	DrawRotaGraph(512, 384, 1, 0, backGroundGh, false);



	/*const float* test = testShip->GetShipStatus();

	for (int i = 0; i < 5; ++i) {
		DrawStringEx(200, 200 + (50 * i), GetColor(0,0,0), "%f", test[i]);
	}*/


}
