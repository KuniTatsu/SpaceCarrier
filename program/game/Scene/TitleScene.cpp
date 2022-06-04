#include "TitleScene.h"
#include"../Manager/GameManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/PartsManager.h"
//#include"../Ship.h"
#include"../Inventory.h"
#include"../GraphicUI.h"

//#include"Object.h"

TitleScene::TitleScene()
{
	gManager = GameManager::Instance();
	//testGh = gManager->LoadGraphEx("graphics/test_1.png");
	backGroundGh = gManager->LoadGraphEx("graphics/TestTitle.png");

	//-----------------------debugtest--------------------------------------//
	//testShip = new Ship();
	pManager = PartsManager::Instance();
	testInventory = new Inventory();
	//----------------------------------------------------------------------//
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	//-----------------------debugtest--------------------------------------//
	if (!init) {
		testInventory->AddInventory(100);
		testInventory->AddInventory(102);
		testInventory->AddInventory(104);
		testInventory->AddInventory(106);
		testInventory->AddInventory(109);

		backWidth = (guideX + 190) - (guideX - 70);
		backHeight = 310;

		back = std::make_shared<GraphicUI>(tnl::Vector3(guideX - 70, 30, 0), backWidth, backHeight, "graphics/FrameBlack.png", "");

		init = true;
	}
	/*if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_UP)) {
		guideY -= 10;
	}
	else if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_DOWN)) {
		guideY += 10;
	}*/

	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_P)) {
		auto newPartsId = pManager->GetRandomPartsId();
		testInventory->AddInventory(newPartsId);
	}


	//---------------------------------------------------------------------//

	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
		return;
	}

}

void TitleScene::Draw()
{
	DrawRotaGraph(512, 384, 1, 0, backGroundGh, false);

	//-----------------------debugtest--------------------------------------//
	back->Draw();

	testInventory->InventoryDraw(testInventory->guideX - 70, 30, testInventory->guideX + 190, 340);

	/*const float* test = testShip->GetShipStatus();

	for (int i = 0; i < 5; ++i) {
		DrawStringEx(200, 200 + (50 * i), GetColor(0,0,0), "%f", test[i]);
	}*/

	//---------------------------------------------------------------------//
}
