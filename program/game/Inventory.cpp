#include "Inventory.h"
#include"ShipParts/ShipParts.h"
#include"ShipParts/PartsBase.h"
#include"../dxlib_ext/dxlib_ext.h"
#include"Manager/PartsManager.h"

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

void Inventory::AddInventory(std::shared_ptr<ShipParts> Parts)
{
	inventory.emplace_back(Parts);
}
void Inventory::AddInventory(int PartsId)
{
	auto addParts = std::dynamic_pointer_cast<ShipParts, PartsBase>(pManager->GetParts(PartsId));
	inventory.emplace_back(addParts);
}
//インベントリ内のパーツを2列で羅列して表示する関数
void Inventory::InventoryDraw(int GuideX, int GuideY, int FrameTopX, int FrameTopY, int FrameBottomX, int FrameBottomY)
{
	//描画範囲を限定する(この範囲内から出たら描画されない)
	SetDrawArea(FrameTopX, FrameTopY, FrameBottomX, FrameBottomY);

	auto parts = inventory.begin();
	for (int i = 0; i < inventory.size(); ++i) {

		int y = GuideY + (i / 2) * 120;



		//GuideXとGuideYを動かすことで全てのパーツ画像を動かす
		//偶数なら右側
		if (i % 2 == 0) {
			(*parts)->DrawPartsIcon(GuideX + 120, y);
		}
		//奇数なら左側
		else {
			(*parts)->DrawPartsIcon(GuideX, y);
		}
		parts++;
	}
	//描画エリアを元に戻す
	SetDrawArea(0, 0, 1024, 768);
}
