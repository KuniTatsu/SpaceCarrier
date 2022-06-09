#include "Inventory.h"
#include"ShipParts/ShipParts.h"
#include"ShipParts/PartsBase.h"
#include"ShipParts/WeaponParts.h"
#include"../dxlib_ext/dxlib_ext.h"
#include"Manager/PartsManager.h"
#include"Manager/GameManager.h"
#include"GraphicUI.h"


Inventory::Inventory()
{
	pManager = PartsManager::Instance();
	gManager = GameManager::Instance();
	Init();
}

Inventory::~Inventory()
{
}

void Inventory::Init()
{
	inventoryFrameGh = gManager->LoadGraphEx("graphics/InventoryFrame.png");
}
//--------------船のパーツをインベントリに追加する関数群-----------------------//
void Inventory::AddInventory(std::shared_ptr<ShipParts> Parts)
{
	inventory.emplace_back(Parts);
}
//パーツIDからインベントリにパーツを追加する関数
void Inventory::AddInventory(int PartsId)
{
	auto addParts = std::dynamic_pointer_cast<ShipParts, PartsBase>(pManager->GetParts(PartsId));
	inventory.emplace_back(addParts);
}

//--------------船の武器パーツをインベントリに追加する関数-------------------//
void Inventory::AddWeaponInventory(std::shared_ptr<WeaponParts> Parts)
{
	weaponInventory.emplace_back(Parts);
}

void Inventory::AddWeaponInventory(int PartsId)
{
	//auto addParts = std::dynamic_pointer_cast<WeaponParts, PartsBase>(pManager->GetWeaponParts(PartsId));
	auto addParts = std::dynamic_pointer_cast<WeaponParts, PartsBase>(pManager->GetWeaponParts(PartsId));

	weaponInventory.emplace_back(addParts);
}

void Inventory::InventoryMove()
{
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_UP)) {
		if (guideY >= 145)return;
		guideY += 10;
	}
	else if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_DOWN)) {
		guideY -= 10;
	}
}

void Inventory::InventorySelect()
{
	//auto parts = inventory.begin();

	for (auto parts : inventory) {
		parts->isClicked(gManager->mousePosX, gManager->mousePosY);
	}
}

//インベントリ内のパーツを2列で羅列して表示する関数
void Inventory::InventoryDraw(int FrameTopX, int FrameTopY, int FrameBottomX, int FrameBottomY)
{
	//描画範囲を限定する(この範囲内から出たら描画されない)
	SetDrawArea(FrameTopX, FrameTopY, FrameBottomX, FrameBottomY - 1);
	auto parts = inventory.begin();
	for (int i = 0; i < inventory.size(); ++i) {

		//中央揃えのための文字列の長さ取得
		auto length = (*parts)->GetStrLength();

		//パーツごとの描画するy座標 画像同士の幅をあける
		int y = guideY + (i / 2) * 230;

		//GuideYを動かすことで全てのパーツ画像を動かす
		//偶数なら左側
		if (i % 2 == 0) {
			(*parts)->DrawPartsIcon(guideX, y);

			//パーツ名の描画 (180-length/2)は表示可能領域の中央座標を求める式
			DrawStringEx(-80 + (180 - length / 2), y - 100, GetColor(0, 0, 0), (*parts)->GetFactName().c_str());
		}
		//奇数なら右側
		else {
			(*parts)->DrawPartsIcon(guideX + 180, y);

			//パーツ名の描画
			DrawStringEx(110 + (180 - length / 2), y - 100, GetColor(0, 0, 0), (*parts)->GetFactName().c_str());
		}

		parts++;
	}
	//描画エリアを元に戻す
	SetDrawArea(0, 0, 1024, 768);

	//最外枠の画像の描画
	auto center = tnl::Vector3(FrameTopX + ((FrameBottomX - FrameTopX) / 2 - 1), FrameTopY + ((FrameBottomY - FrameTopY) / 2), 0);
	DrawRotaGraph(center.x, center.y, 1.5, 0, inventoryFrameGh, true);


}
