//プレイヤーが所持するアイテム,パーツを保持するインベントリクラス
#pragma once
#include<list>
#include<memory>

class PartsBase;
class ShipParts;
class WeaponParts;

class GraphicUI;
class PartsManager;
class GameManager;

class Inventory
{
public:
	Inventory();
	~Inventory();

	void Init();

	//inventoryに船のパーツを追加する関数
	void AddInventory(std::shared_ptr<ShipParts>Parts);
	void AddInventory(int PartsId);

	//inventoryに武器パーツを追加する関数
	void AddWeaponInventory(std::shared_ptr<WeaponParts>Parts);
	void AddWeaponInventory(int PartsId);

	//船体パーツインベントリを取得する関数
	inline std::list<std::shared_ptr<ShipParts>>& GetPartsInventory() {
		return inventory;
	}

	//武器インベントリを取得する関数
	inline std::list<std::shared_ptr<WeaponParts>>& GetWeaponInventory() {
		return weaponInventory;
	}

	//inventoryの中身を全削除する関数
	inline void CleanInventory() {
		inventory.clear();
	}
	//インベントリ内のアイコンリストをスクロールする関数
	void InventoryMove();

	//インベントリ内のパーツがクリックされたか感知する関数
	std::shared_ptr<ShipParts> InventorySelect();

	//インベントリ内のアイコン画像を描画する関数
	void InventoryDraw(int FrameTopX, int FrameTopY, int FrameBottomX, int FrameBottomY);


	//インベントリ内の画像の基準点画像
	int guideX = 100;
	int guideY = 145;

private:
	//船のパーツのインベントリ
	std::list<std::shared_ptr<ShipParts>>inventory;

	//inventoryの枠の画像ハンドル
	int inventoryFrameGh = 0;
	//背景の画像ハンドル
	int inventoryBackGh = 0;

	//武器パーツのインベントリ
	std::list<std::shared_ptr<WeaponParts>>weaponInventory;

	PartsManager* pManager = nullptr;

	GameManager* gManager = nullptr;
	//インベントリの背景画像
	std::shared_ptr<GraphicUI>back;

	enum class DRAWINVENTORY :uint32_t {
		SHIPPARTS,
		WEAPON,
		MAX
	};



};


