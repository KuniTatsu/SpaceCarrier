#include "CustomizeScene.h"
#include"../Manager/GameManager.h"
#include"../Object/Player.h"
#include"../Manager/SceneManager.h"

CustomizeScene::CustomizeScene()
{
	Init();
}

CustomizeScene::~CustomizeScene()
{
}

void CustomizeScene::Update()
{
	player->InventoryUpdate();

	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_R)) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
	}

}

void CustomizeScene::Draw()
{
	player->DrawInventory();
	player->DrawShip();
	
	DrawStringEx(700, 200, -1, "R�L�[�ŃX�e�[�W�Z���N�g�֖߂�");
}

void CustomizeScene::Init()
{
	gManager = GameManager::Instance();
	player = gManager->GetPlayer();
}
