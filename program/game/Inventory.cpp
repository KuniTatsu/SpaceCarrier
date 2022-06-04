#include "Inventory.h"
#include"ShipParts/ShipParts.h"
#include"ShipParts/PartsBase.h"
#include"ShipParts/WeaponParts.h"
#include"../dxlib_ext/dxlib_ext.h"
#include"Manager/PartsManager.h"
#include"GraphicUI.h"


Inventory::Inventory()
{
	pManager = PartsManager::Instance();
}

Inventory::~Inventory()
{
}

void Inventory::Init()
{

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
		guideY -= 10;
	}
	else if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_DOWN)) {
		guideY += 10;
	}
}

//インベントリ内のパーツを2列で羅列して表示する関数
void Inventory::InventoryDraw(int FrameTopX, int FrameTopY, int FrameBottomX, int FrameBottomY)
{
	//描画範囲を限定する(この範囲内から出たら描画されない)
	SetDrawArea(FrameTopX, FrameTopY, FrameBottomX, FrameBottomY);


	auto parts = inventory.begin();
	for (int i = 0; i < inventory.size(); ++i) {

		int y = guideY + (i / 2) * 120;
		//GuideXとGuideYを動かすことで全てのパーツ画像を動かす
		//偶数なら左側
		if (i % 2 == 0) {
			(*parts)->DrawPartsIcon(guideX, y);
		}
		//奇数なら右側
		else {
			(*parts)->DrawPartsIcon(guideX + 120, y);
		}
		parts++;
	}
	//描画エリアを元に戻す
	SetDrawArea(0, 0, 1024, 768);
}
