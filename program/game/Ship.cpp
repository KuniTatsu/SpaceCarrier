#include "Ship.h"
#include"ShipParts/ShipParts.h"
#include"ShipParts/WeaponParts.h"
#include"Manager/PartsManager.h"
#include"Manager/GameManager.h"

Ship::Ship()
{
	ShipInit();
}

Ship::~Ship()
{
}

void Ship::DrawShipParts()
{
	for (auto parts : shipParts) {
		parts->DrawParts(gManager->Center.x + 250, gManager->Center.y - 160);
	}
}
//--------船生成時に一度だけ呼ぶ初期所持パーツ登録関数---------//
void Ship::SetProtoParts(std::shared_ptr<ShipParts>Parts)
{
	Parts->ChangeEquiped();
	shipParts.emplace_back(Parts);
}

void Ship::SetProtoWeapon(std::shared_ptr<WeaponParts> Weapon)
{

	weapones.emplace_back(Weapon);
}
//------------------------------------------------------------//

void Ship::ShipInit()
{
	//パーツマネージャ取得
	pManager = PartsManager::Instance();
	gManager = GameManager::Instance();
	/*
	//船の初期パーツを登録する
	pManager->SetProtoTypeParts(shipParts);
	//船の初期武器を登録する
	pManager->SetProtoTypeWeapon(weapones);
	*/
}
//船のステータスのセット
void Ship::SetShipStatus()
{
	//今の船のステータスを一旦全て0にする
	ClearShipStatus();

	//各パーツの基本ステータス配列を取得する

	//各パーツのステータス配列が入った配列:二次元配列
	float* partsStatus[5] = {};
	for (int i = 0; i < shipParts.size(); ++i) {
		partsStatus[i] = shipParts[i]->GetTrueStatus();
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

//ステータスリセット関数
void Ship::ClearShipStatus()
{
	for (int i = 0; i < 5; ++i) {
		shipStatus[i] = 0;
	}
}
//-------船のパーツ換装関数---------------//
void Ship::ChangeShipParts(int PartsType, std::shared_ptr<ShipParts> NewParts)
{
	//装備中パーツの装備状態を更新する
	shipParts[PartsType]->ChangeEquiped();

	//装備中のパーツを外す
	shipParts[PartsType] = nullptr;

	//所持している換装対象のパーツを装備する
	shipParts[PartsType] = NewParts;
	shipParts[PartsType]->ChangeEquiped();

	//ステータスを再計算する
	SetShipStatus();
}

//-----------射撃系関数-------------//
void Ship::ShootShipWeapon()
{
	for (auto weapon : weapones) {
		weapon->ShootBullet(gManager->deltatime);
	}
}

void Ship::AllWeaponCoolDawnUpdate()
{
	for (auto weapon : weapones) {
		weapon->WeaponUpdate();
	}
}

float Ship::GetCoolDown(int WeaponNum)
{
	return weapones[WeaponNum]->GetWeaponCoolDawn();
}
