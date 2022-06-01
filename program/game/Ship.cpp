#include "Ship.h"
#include"ShipParts/ShipParts.h"
#include"Manager/PartsManager.h"

Ship::Ship()
{
	ShipInit();
}

Ship::~Ship()
{
}

void Ship::ShipInit()
{
	//パーツマネージャ取得
	pManager = PartsManager::Instance();

	//船の初期パーツを登録する
	pManager->SetProtoTypeParts(shipParts);
	//船の初期武器を登録する
	pManager->SetProtoTypeWeapon(weapones);

	//船のステータス各種合計を取得
	SetShipStatus();
}

void Ship::SetShipStatus()
{
	//今の船のステータスを一旦全て0にする
	ClearShipStatus();

	//各パーツの基本ステータス配列を取得する

	//各パーツの基本ステータス配列が入った配列:二次元配列
	float* partsStatus[5] = {};
	for (int i = 0; i < shipParts.size(); ++i) {
		partsStatus[i] = std::dynamic_pointer_cast<ShipParts, PartsBase>(shipParts[i])->GetPartsStatus();
	}

	//二次元配列の各配列番号ごとに足して船のステータスに代入する
	//パーツごと
	for (int i = 0; i < 5; ++i) {
		//各ステータス
		for (int k = 0; k < 5; ++k) {
			if (partsStatus[i] == nullptr)continue;
			shipStatus[k] += partsStatus[i][k];
		}
	}

}

void Ship::ClearShipStatus()
{
	for (int i = 0; i < 5; ++i) {
		shipStatus[i] = 0;
	}
}
//-------船のパーツ換装関数---------------//
void Ship::ChangeShipParts(int PartsType, std::shared_ptr<PartsBase> NewParts)
{
	//装備中のパーツを外す
	shipParts[PartsType] = nullptr;

	//所持している換装対象のパーツを装備する
	shipParts[PartsType] = NewParts;
}

void Ship::ShootShipWeapon()
{
}
