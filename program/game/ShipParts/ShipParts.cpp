#include "ShipParts.h"
#include"../Manager/GameManager.h"

ShipParts::ShipParts(int Id, int PartsType, std::string Name, float Hp, float Energy, float Defence, float Speed, std::string GhPass,
							std::string IconPass,float ContainerAmount)
{
	gManager = GameManager::Instance();

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

	//-------------修飾Modの決定(ありなし含む)------------------//
	//個数は0~2個



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
	DrawRotaGraph(X, Y, 1, 0, iconGh, true);
}
