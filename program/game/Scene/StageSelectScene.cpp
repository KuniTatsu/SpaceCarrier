#include "StageSelectScene.h"
#include"../Manager/GameManager.h"
#include"../Manager/UIManager.h"
#include"../GraphicUI.h"
#include"../Manager/SceneManager.h"
#include"../Object/Player.h"
#include"../Observer.h"
#include"../Menu.h"

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
	auto pos = customMenu->GetTopPos();

	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_C)||
		gManager->isClickedRect(gManager->mousePosX, gManager->mousePosY,pos.x,pos.y, pos.x+customMenu->GetWidth(), pos.y+ customMenu->GetHeight())
		) {
		SceneManager::ChangeScene(SceneManager::SCENE::CUSTOM);
		return;
	}

}

void StageSelectScene::Draw()
{
	uiManager->DrawUI();

	customMenu->MenuDraw();
	auto pos = customMenu->GetTopPos();

	SetFontSize(20);
	DrawStringEx(pos.x + 80, pos.y + 35, -1, "�J�X�^�}�C�Y");
	SetFontSize(16);

	DrawStringEx(700, 150, -1, "C�L�[�ŃJ�X�^�}�C�Y�V�[���Ɉړ�����");
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

	customMenu = std::make_shared<Menu>(362, 500, 300, 80, "graphics/FrameBlack.png");

	//player�̃C���X�^���X�擾
	player = gManager->CreatePlayer();

}

void StageSelectScene::CreateStage()
{
	if (selectNum == 0) {
		gManager->SetMyStage(GameManager::STAGE::SOL);
		SceneManager::ChangeScene(SceneManager::SCENE::INGAME);
	}
}
