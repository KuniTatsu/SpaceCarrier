#include "CustomizeScene.h"
#include"../Manager/GameManager.h"
#include"../Object/Player.h"
#include"../Manager/SceneManager.h"
#include"../Menu.h"
#include"../ShipParts/ShipParts.h"
#include"../Ship.h"

CustomizeScene::CustomizeScene()
{
	Init();
}

CustomizeScene::~CustomizeScene()
{
}

void CustomizeScene::Update()
{

	/*if (sceneChange) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
		return;
	}*/
	//シークエンスでfalseが帰ってきたらシーンを移動する
	if (!mainSeqence.update(gManager->deltatime)) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
	}

	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_R)) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
	}

}

void CustomizeScene::Draw()
{
	//背景の描画
	DrawRotaGraph(gManager->Center.x, gManager->Center.y, 1, 0, background, false);

	//シークエンスごとのDraw関数
	drawFunc(this);


	DrawStringEx(700, 200, -1, "Rキーでステージセレクトへ戻る");
}

void CustomizeScene::Init()
{
	gManager = GameManager::Instance();
	player = gManager->GetPlayer();

	playerShip = player->GetShip();

	menuShipCustomGh = gManager->LoadGraphEx("graphics/CustomMenu_1.png");
	menuWeaponCustomGh = gManager->LoadGraphEx("graphics/CustomMenu_2.png");
	menuReturnGh = gManager->LoadGraphEx("graphics/CustomMenu_3.png");

	ghs.emplace_back(menuShipCustomGh);
	ghs.emplace_back(menuWeaponCustomGh);
	ghs.emplace_back(menuReturnGh);

	background = gManager->LoadGraphEx("graphics/BackGroundCustomScene.png");
	highright = gManager->LoadGraphEx("graphics/CustomMenu_HighLight.png");

	partsEquipMenu = std::make_shared<SelectMenu>(400, 300, 120, 80, "graphics/FrameBlack.png");

	partsEquipMenu->AddMenuElements("装備する");
	partsEquipMenu->AddMenuElements("やめる");

}

bool CustomizeScene::SeqTop(const float deltatime)
{

	//船のカスタマイズをクリックしたら
	//ChangeSequence(sequence::SELECT);

	//各menu画像とマウスの判定
	for (int i = 0; i < 3; ++i) {
		if (gManager->isClickedRect(gManager->mousePosX, gManager->mousePosY, GRAPHICCENTER[i].x - (GRAPHICSIZE / 2), GRAPHICCENTER[i].y - (GRAPHICSIZE / 2),
			GRAPHICCENTER[i].x + (GRAPHICSIZE / 2), GRAPHICCENTER[i].y + (GRAPHICSIZE / 2))) {

			//クリックしたのが戻るだった場合は
			if (i == 2) {
				//SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
				return false;
			}
			//それ以外は各シークエンスに飛ぶ
			ChangeSequence(SEQ[i]);
		}
	}
	return true;
}

bool CustomizeScene::SeqSelect(const float deltatime)
{
	//クリックしたら警告画像を消す
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		isCaution = false;
		return true;
	}

	//もしインベントリ内のパーツをクリックして選択したら
	if (player->InventoryUpdate(selectedParts)) {
		//すでに装備しているパーツをクリックしていたら
		if (selectedParts->IsEquiped()) {

			//すでに装備している旨を表示する
			isCaution = true;
			return true;
		}

		ChangeSequence(sequence::SHIPCUSTOM);
		return true;
		//customシークエンスに移る

	}

	//戻るボタンをクリックしたら
	if (gManager->isClickedRect(gManager->mousePosX, gManager->mousePosY, GRAPHICCENTER[2].x - (GRAPHICSIZE / 2), GRAPHICCENTER[2].y - (GRAPHICSIZE / 2),
		GRAPHICCENTER[2].x + (GRAPHICSIZE / 2), GRAPHICCENTER[2].y + (GRAPHICSIZE / 2))) {
		ChangeSequence(sequence::TOP);
		return true;
	}
	return true;
}

bool CustomizeScene::SeqShipCustomize(const float deltatime)
{
	//menuを表示

	//装備する,やめる
	//menuの移動
	partsEquipMenu->MenuUpdate();

	//enterキーを押したら決定,nowSelectNumによって動作を変える
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		//----------------装備の変更--------------------------//
		if (partsEquipMenu->GetNowSelectNum() == 0) {
			//装備を変更する
			auto type = selectedParts->GetPartsType();
			player->ChangeShipParts(type, selectedParts);

			//パーツ変更完了通知を出す
			//ポップメッセージ？ウィンドウ？

			//selectシークエンスに戻る
			ChangeSequence(sequence::SELECT);
			return true;
		}
		//-----------------selectシークエンスに戻る------------//
		else if (partsEquipMenu->GetNowSelectNum() == 1) {

			//selectシークエンスに戻る
			ChangeSequence(sequence::SELECT);

			//menuを0に戻す
			partsEquipMenu->ResetMenuNum();
			return true;
		}
	}

	//どちらかを行うまでシークエンスを出ない
	//装備するを押したらパーツタイプを読み取り、
	//shipのchangeShipParts関数を呼ぶ

	//引数にselectedPartsを入れる

	DrawStringEx(500, 500, -1, "カスタマイズシークエンスだよ");
	return true;
}

bool CustomizeScene::SeqWeaponCustomize(const float deltatime)
{
	return true;
}

void CustomizeScene::ChangeSequence(const sequence seq)
{
	//今のシークエンスと一つ前のシークエンスをそれぞれ更新
	lastSeq = nowSeq;
	nowSeq = seq;

	//シークエンスを切り替える
	switch (seq)
	{
	case sequence::TOP: {
		mainSeqence.change(&CustomizeScene::SeqTop);
		//描画対象をセレクトシーンに変更する
		drawFunc = &CustomizeScene::DrawTopSeq;
		break;
	}
	case sequence::SELECT: {
		mainSeqence.change(&CustomizeScene::SeqSelect);
		//描画対象をセレクトシーンに変更する
		drawFunc = &CustomizeScene::DrawSelectSeq;
		break;
	}
	case sequence::SHIPCUSTOM: {
		mainSeqence.change(&CustomizeScene::SeqShipCustomize);
		//描画対象をカスタマイズシーンに変更する
		drawFunc = &CustomizeScene::DrawCustomSeq;
		break;
	}
	case sequence::WEAPONCUSTOM: {
		mainSeqence.change(&CustomizeScene::SeqWeaponCustomize);
		drawFunc = &CustomizeScene::DrawWeaponSeq;
		break;
	}
	default:
		break;
	}
}

void CustomizeScene::DrawTopSeq()
{

	//各menu画像とマウスの判定
	for (int i = 0; i < 3; ++i) {
		if (gManager->OnMouseRect(gManager->mousePosX, gManager->mousePosY, GRAPHICCENTER[i].x - (GRAPHICSIZE / 2), GRAPHICCENTER[i].y - (GRAPHICSIZE / 2),
			GRAPHICCENTER[i].x + (GRAPHICSIZE / 2), GRAPHICCENTER[i].y + (GRAPHICSIZE / 2))) {
			//メニューをハイライト表示する
			DrawRotaGraph(GRAPHICCENTER[i].x, GRAPHICCENTER[i].y, 0.8, 0, highright, false);
		}
	}
	//各menu画像の描画
	int i = 0;
	for (auto gh : ghs) {
		DrawRotaGraph(200 + i * 320, 600, 0.8, 0, gh, false);
		++i;
	}
}

void CustomizeScene::DrawSelectSeq()
{
	//パーツインベントリの描画
	player->DrawInventory();
	player->DrawShip();

	//戻るボタンの描画とハイライト表示
	if (gManager->OnMouseRect(gManager->mousePosX, gManager->mousePosY, GRAPHICCENTER[2].x - (GRAPHICSIZE / 2), GRAPHICCENTER[2].y - (GRAPHICSIZE / 2),
		GRAPHICCENTER[2].x + (GRAPHICSIZE / 2), GRAPHICCENTER[2].y + (GRAPHICSIZE / 2))) {
		//メニューをハイライト表示する
		DrawRotaGraph(GRAPHICCENTER[2].x, GRAPHICCENTER[2].y, 0.8, 0, highright, false);
	}
	DrawRotaGraph(GRAPHICCENTER[2].x, GRAPHICCENTER[2].y, 0.8, 0, ghs[2], false);
}

void CustomizeScene::DrawCustomSeq()
{
	//パーツインベントリの描画
	player->DrawInventory();
	player->DrawShip();

	//装備選択メニューの描画
	partsEquipMenu->DrawSelectMenu();

	auto shipStatus = playerShip->GetShipStatus();

	/*for (int i = 0; i < 5; ++i) {
		DrawStringEx()
	}*/

}

void CustomizeScene::DrawWeaponSeq()
{
}
