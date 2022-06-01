#include "TitleScene.h"
#include"../Manager/GameManager.h"
#include"../Manager/SceneManager.h"
//#include"../Ship.h"
#include"../Inventory.h"

//#include"Object.h"

TitleScene::TitleScene()
{
	gManager = GameManager::Instance();
	//testGh = gManager->LoadGraphEx("graphics/test_1.png");
	backGroundGh = gManager->LoadGraphEx("graphics/TestTitle.png");

	//testShip = new Ship();
	testInventory = new Inventory();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (!init) {
		testInventory->AddInventory(100);
		testInventory->AddInventory(102);
		testInventory->AddInventory(104);
		testInventory->AddInventory(106);
		testInventory->AddInventory(109);
		init = true;
	}
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_UP)) {
		guideY -= 10;
	}
	else if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_DOWN)) {
		guideY += 10;
	}

	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
		return;
	}

}

void TitleScene::Draw()
{
	//DrawRotaGraph(512, 384, 1, 0, backGroundGh, false);


	testInventory->InventoryDraw(guideX, guideY, guideX - 50 - 20, 30, guideX + 170 + 20, 340);

	/*const float* test = testShip->GetShipStatus();

	for (int i = 0; i < 5; ++i) {
		DrawStringEx(200, 200 + (50 * i), GetColor(0,0,0), "%f", test[i]);
	}*/


}
