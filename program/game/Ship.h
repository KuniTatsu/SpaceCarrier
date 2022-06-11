//playerの船の情報クラス
//各種パーツのポインタを持つ
#pragma once
#include<vector>
#include<memory>

class PartsBase;
class ShipParts;
class WeaponParts;
class PartsManager;
class GameManager;

class Ship
{
public:
	Ship();
	~Ship();

	//船の基本ステータス取得関数
	inline const float* GetShipStatus() {
		return shipStatus;
	}

	//船のパーツの描画関数
	void DrawShipParts();

	//船の初期パーツ登録関数
	void SetProtoParts(std::shared_ptr<ShipParts>Parts);

	//船の初期武器登録関数
	void SetProtoWeapon(std::shared_ptr<WeaponParts>Weapon);

	//搭載パーツの各ステータス合計を出す関数
	void SetShipStatus();

	//搭載武器全てで射撃する関数
	void ShootShipWeapon();

	//搭載武器全てのクールダウンの更新関数
	void AllWeaponCoolDawnUpdate();

	//搭載武器全てのクールダウン取得関数
	float GetCoolDown(int WeaponNum);

	//船の現在装備中の武器の数を返す関数
	inline int GetWeaponNum() {
		return weapones.size();
	}

	//船のパーツを変更する関数
	void ChangeShipParts(int PartsType, std::shared_ptr<ShipParts> NewParts);

	//船に装備しているパーツ一覧を返す関数
	inline const std::vector<std::shared_ptr<ShipParts>>& GetShipPartsList() {
		return shipParts;
	}

private:

	//初期化関数
	void ShipInit();

	//パーツマネージャポインタ
	PartsManager* pManager = nullptr;
	//ゲームマネージャポインタ
	GameManager* gManager = nullptr;

	enum class PARTS :uint32_t {
		HULL,
		CONTAINER,
		ARMOR,
		GENERATOR,
		THRUSTER,
		MAX
	};

	enum class WEAPON :uint32_t {
		MAIN,
		SUB,
		MAX
	};
	//各パーツのポインタ
	//std::shared_ptr<PartsBase> shipParts[static_cast<uint32_t>(PARTS::MAX)] = { nullptr,nullptr, nullptr, nullptr, nullptr };

	//船に装備しているパーツ
	std::vector<std::shared_ptr<ShipParts>>shipParts = {};


	/*
	//------各パーツのポインタ---------
	//船体パーツ
	PartsBase* hull = nullptr;
	//貨物室パーツ
	PartsBase* container = nullptr;
	//装甲パーツ
	PartsBase* armor = nullptr;
	//発電機パーツ
	PartsBase* generator = nullptr;
	//スラスターパーツ
	PartsBase* thruster = nullptr;
	*/
	/*
	//武器1
	PartsBase* mainWeapon = nullptr;
	//武器2
	PartsBase* subWeapon = nullptr;
	*/

	//搭載武器配列	いずれいくつも武器を搭載できるようにvectorで実装
	std::vector<std::shared_ptr<WeaponParts>>weapones;

	//main武器搭載可能量
	int allowMainWeaponNum = 1;
	//sub武器搭載可能量
	int allowSubWeaponNum = 1;

	enum class STATUS :uint32_t {
		HP,
		ENERGY,
		DEFENCE,
		SPEED,
		CONTAINER,
		MAX
	};
	//搭載パーツの合計ステータス hp,energy,defence,speed,container
	float shipStatus[static_cast<uint32_t>(STATUS::MAX)] = { 0,0,0,0,0 };


	//船のステータスの初期化
	void ClearShipStatus();

	/*
	//-------搭載パーツの合計ステータス
	//体力
	float hp = 0;
	//必要電力
	float energy = 0;
	//防御力
	float defence = 0;
	//速度
	float speed = 0;
	//積載可能量
	float containerAmount = 0;
	*/




};

