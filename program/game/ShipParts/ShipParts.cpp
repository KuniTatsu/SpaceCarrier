#include "ShipParts.h"
#include"../Manager/GameManager.h"
#include"../Manager/ModManager.h"
#include"../Mod.h"
#include"../Menu.h"

ShipParts::ShipParts(int Id, int PartsType, std::string Name, float Hp, float Energy, float Defence, float Speed, std::string GhPass,
	std::string IconPass, float ContainerAmount)
{
	gManager = GameManager::Instance();
	mManager = ModManager::Instance();

	//------------基本データの代入------------------//
	partsId = Id;
	partsType = PartsType;

	partsName = Name;

	hp = Hp;
	energy = Energy;
	defence = Defence;
	speed = Speed;
	containerAmount = ContainerAmount;

	basicStatus[0] = hp;
	basicStatus[1] = energy;
	basicStatus[2] = defence;
	basicStatus[3] = speed;
	basicStatus[4] = containerAmount;

	pass = GhPass;
	gh = gManager->LoadGraphEx(GhPass);

	iconPass = IconPass;
	iconGh = gManager->LoadGraphEx(IconPass);

	iconBachGh = gManager->LoadGraphEx("graphics/ShipParts/Icon_Back_fix.png");
	iconEquipGh = gManager->LoadGraphEx("graphics/ShipParts/Icon_Back_Equiped.png");

	highRight = gManager->LoadGraphEx("graphics/ShipParts/Icon_Back_test.png");

	statusBack = std::make_shared<Menu>(500, 320, 140, 120, "graphics/FrameBlack.png");

	modNameBack = std::make_shared<Menu>(400, 320, 90, 120, "graphics/FrameBlack.png");

	//以下の処理はマスター生成時には実行しない
	if (!gManager->GetLoadedFlag())return;

	//-------------修飾Modの決定(ありなし含む)------------------//
	//個数は0~2個
	//0:1:2=40:50:10%
	int modNum = 0;

	int rand = GetRand(100);
	if (rand >= 40 && rand < 90)modNum = 1;
	else if (rand >= 90)modNum = 2;

	//もしmodがつかないパーツならここで名前を決めて処理を終える
	if (modNum == 0) {
		factName = partsName;

		//名前の長さを取得する(中央揃えで描画するため)
		// 文字列の長さを取得
		int StrLen = strlen(factName.c_str());

		// 描画時の文字列の幅を取得
		strWidth = GetDrawStringWidth(factName.c_str(), StrLen);

		//合計ステータスの取得
		SetTrueStatus();
		return;
	}

	//modNumの個数分modを付与する
	for (int i = 0; i <= modNum; ++i) {
		auto mod = mManager->CreateNewMod();
		myMods.emplace_back(mod);
		//tnl::DebugTrace("\n修飾Mod[%s]を付与しました\n", mod->GetModName().c_str());
	}
	//Modステータスの取得
	SetEditStatus();
	//合計ステータスの取得
	SetTrueStatus();

	//１つ目のModの名前をパーツの名前に加えて表示する
	factName = myMods[0]->GetModName() + partsName;

	// 文字列の長さを取得
	int StrLen = strlen(factName.c_str());

	// 描画時の文字列の幅を取得
	strWidth = GetDrawStringWidth(factName.c_str(), StrLen);
}

ShipParts::~ShipParts()
{
}

void ShipParts::DrawParts(int X, int Y)
{
	DrawRotaGraph(X, Y, 1, 0, gh, true);
}

void ShipParts::DrawPartsIcon(int X, int Y)
{
	//-----------ハイライト表示--------------
	//マウスがアイコン画像の中にあればそのアイコン画像の背景をハイライトする
	if (gManager->mousePosX >= X - 90 && gManager->mousePosX <= X + 90 &&
		gManager->mousePosY >= Y - 112 && gManager->mousePosY <= Y + 112
		) {
		DrawRotaGraph(X, Y, 1.5, 0, highRight, false);
		if (!isCursored)isCursored = true;
	}
	else {
		if (isCursored)isCursored = false;
	}
	//-----------------------------

	//装備されていたら背景画像を変える
	if (isEquiped) DrawRotaGraph(X, Y, 1.5, 0, iconEquipGh, true);
	else DrawRotaGraph(X, Y, 1.5, 0, iconBachGh, true);

	DrawRotaGraph(X, Y, 1.5, 0, iconGh, false);

	iconCenter.x = X;
	iconCenter.y = Y;

	////マウスがアイコン画像の中にあればその装備のステータスを表示する
	//if (gManager->mousePosX >= X - 90 && gManager->mousePosX <= X + 90 &&
	//	gManager->mousePosY >= Y - 112 && gManager->mousePosY <= Y + 112)
	//{
	//	statusBack->MenuDraw();

	//	auto pos = statusBack->GetTopPos();
	//	DrawPartsStatus(pos.x + 10, pos.y + 10);
	//}


}
//修飾Modの持つステータスの合計
void ShipParts::SetEditStatus()
{
	//modを持たないなら計算しない
	if (myMods.empty()) {
		for (int i = 0; i < 5; ++i) {
			addStatus[i] = 0;
		}
		return;
	}

	//全てのModからステータスをそれぞれ加算する
	for (auto mod : myMods) {

		auto status = mod->GetBasicStatus();

		addHp += status[0];
		addEnergy += status[1];
		addDefence += status[2];
		addSpeed += status[3];
		addContainerAmount += status[4];

		//配列にも入れておく
		for (int i = 0; i < 5; ++i) {
			addStatus[i] += status[i];
		}
	}
}

void ShipParts::SetTrueStatus()
{
	for (int i = 0; i < 5; ++i) {
		trueStatus[i] = basicStatus[i] + addStatus[i];
	}
}

bool ShipParts::isClicked(int MouseX, int MouseY)
{
	//アイコン画像の幅は180 縦は225
	//iconXとiconYは描画中心座標

	//iconX-90 ->iconX+90の範囲内にいればx座標はアイコンの中にある
	//iconY-112.5 -> iconY+112.5の範囲内にいればy座標はアイコンの中にある

	//もしアイコン画像内にマウスがあり、クリックしていれば
	if (gManager->isClickedRect(MouseX, MouseY, iconCenter.x - 90, iconCenter.y - 112, iconCenter.x + 90, iconCenter.y + 112)) {
		//tnl::DebugTrace("\n%sのアイコン画像がクリックされました\n", factName.c_str());
		return true;
	}

	return false;
}

//ハイライトされたパーツのステータスを描画する関数
void ShipParts::DrawPartsStatus(int TopX, int TopY)
{
	for (int i = 0; i < 5; ++i) {
		DrawStringEx(TopX, TopY + i * 20, -1, STATUSNAME[i].c_str());
		DrawStringEx(TopX + 70, TopY + i * 20, -1, "%.0f", trueStatus[i]);
	}
}

void ShipParts::DrawPartsSet()
{
	statusBack->MenuDraw();

	auto pos = statusBack->GetTopPos();
	DrawPartsStatus(pos.x + 10, pos.y + 10);

	auto modPos = modNameBack->GetTopPos();

	modNameBack->MenuDraw();
	DrawStringEx(modPos.x + 10, modPos.y + 10, -1, "所持MOD");
	if (myMods.empty()) {

		DrawStringEx(modPos.x + 10, modPos.y + 30, -1, "無し");
		return;
	}

	for (int i = 0; i < myMods.size(); ++i) {
		auto name = myMods[i]->GetModName();
		DrawStringEx(modPos.x + 10, modPos.y + 30 + i * 20, -1, name.c_str());
	}


}
