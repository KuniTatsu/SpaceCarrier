//プレイヤーが所持するアイテム,パーツを保持するインベントリクラス
#pragma once
#include<list>
#include<memory>

class PartsBase;
class ShipParts;

class GraphicUI;
class PartsManager;

class Inventory
{
public:
	Inventory();
	~Inventory();

	void Init();

	//inventoryに追加する関数
	void AddInventory(std::shared_ptr<ShipParts>Parts);
	void AddInventory(int PartsId);

	//inventoryの中身を全削除する関数
	inline void CleanInventory() {
		inventory.clear();
	}

	void InventoryDraw(int GuideX,int GuideY,int FrameTopX, int FrameTopY, int FrameBottomX, int FrameBottomY);

private:
	std::list<std::shared_ptr<ShipParts>>inventory;

	PartsManager* pManager = nullptr;

	std::shared_ptr<GraphicUI>back;
};


