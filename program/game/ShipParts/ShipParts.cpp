#include "ShipParts.h"
#include"../Manager/GameManager.h"
#include"../Manager/ModManager.h"
#include"../Mod.h"

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

	//-------------修飾Modの決定(ありなし含む)------------------//
	//個数は0~2個
	//0:1:2=40:50:10%
	int modNum = 0;

	int rand = GetRand(100);
	if (rand >= 40 && rand < 90)modNum = 1;
	else if (rand >= 90)modNum = 2;

	if (modNum == 0)return;

	//modNumの個数分modを付与する
	for (int i = 0; i <= modNum; ++i) {
		auto mod = mManager->CreateNewMod();
		myMods.emplace_back(mod);
		tnl::DebugTrace("\n修飾Mod[%s]を付与しました\n", mod->GetModName().c_str());
	}
	//１つ目のModの名前をパーツの名前に加えて表示する
	factName = myMods[0]->GetModName() + partsName;
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
	DrawRotaGraph(X, Y, 1.5, 0, iconBachGh, true);
	DrawRotaGraph(X, Y, 1.5, 0, iconGh, false);
}
