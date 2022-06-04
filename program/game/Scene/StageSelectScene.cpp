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


	//UI�̈ړ�,���芴�m
	uiManager->UpdateUI(selectNum);
	//���j���[�����Ȃ�
	if (selectNum != -1) {
		CreateStage();
		return;
	}
	player->InventoryMove();
}

void StageSelectScene::Draw()
{
	uiManager->DrawUI();
	player->DrawInventory();
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

	//ModManager����
	gManager->CreateModManager();
	//Player����
	player = std::make_shared<Player>();
	//GameManager�ɓo�^
	gManager->SetPlayer(player);
	//�D�𐶐�
	player->ShipInit();

	//Observer��player��o�^
	auto observer = gManager->GetObserver();
	observer->SetPlayer(player);
}

void StageSelectScene::CreateStage()
{
	if (selectNum == 0) {
		gManager->SetMyStage(GameManager::STAGE::SOL);
		SceneManager::ChangeScene(SceneManager::SCENE::INGAME);
	}
}
