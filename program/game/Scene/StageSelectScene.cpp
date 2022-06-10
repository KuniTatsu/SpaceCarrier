#include "StageSelectScene.h"
#include"../Manager/GameManager.h"
#include"../Manager/UIManager.h"
#include"../GraphicUI.h"
#include"../Manager/SceneManager.h"
#include"../Object/Player.h"
#include"../Observer.h"

StageSelectScene::StageSelectScene()
{
	Init();
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Update()
{
	//UIの移動,決定感知
	uiManager->UpdateUI(selectNum);
	//メニュー決定後なら
	if (selectNum != -1) {
		CreateStage();
		return;
	}

	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_C)) {
		SceneManager::ChangeScene(SceneManager::SCENE::CUSTOM);
		return;
	}

}

void StageSelectScene::Draw()
{
	uiManager->DrawUI();
	DrawStringEx(700, 150, -1, "Cキーでカスタマイズシーンに移動する");
}

void StageSelectScene::Init()
{
	gManager = GameManager::Instance();
	uiManager = new UIManager(static_cast<int>(GameManager::DIR::HORIZONTAL));

	auto menu1 = std::make_shared<GraphicUI>(tnl::Vector3(UIBASEPOS.x, UIBASEPOS.y, 0), UIWIDTH, UIHEIGHT, "graphics/FrameBlack.png", "graphics/MenuUI_Stage_1.png");
	auto menu2 = std::make_shared<GraphicUI>(tnl::Vector3(UIBASEPOS.x + (DISTANCE + UIWIDTH) * 1, UIBASEPOS.y, 0), UIWIDTH, UIHEIGHT, "graphics/FrameBlack.png", "graphics/MenuUI_Stage_2.png");
	auto menu3 = std::make_shared<GraphicUI>(tnl::Vector3(UIBASEPOS.x + (DISTANCE + UIWIDTH) * 2, UIBASEPOS.y, 0), UIWIDTH, UIHEIGHT, "graphics/FrameBlack.png", "graphics/MenuUI_Stage_3.png");

	uiManager->SetUIList(menu1);
	uiManager->SetUIList(menu2);
	uiManager->SetUIList(menu3);

	//ModManager生成
	gManager->CreateModManager();


	
	//playerのインスタンス取得
	player = gManager->CreatePlayer();

}

void StageSelectScene::CreateStage()
{
	if (selectNum == 0) {
		gManager->SetMyStage(GameManager::STAGE::SOL);
		SceneManager::ChangeScene(SceneManager::SCENE::INGAME);
	}
}
