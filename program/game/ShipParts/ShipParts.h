#pragma once
#include<vector>
#include<memory>
#include<tuple>
#include"PartsBase.h"
#include"../../dxlib_ext/dxlib_ext.h"

class Mod;
class Menu;

class ShipParts :public PartsBase
{
public:
	//id(int)	PartsType(int)	Parts_Name	HP(float)	Atack(float)	Defence(float)	Speed(float)	Gh(std::string)	ContainerAmount
	ShipParts(int Id, int PartsType, std::string Name, float Hp, float Energy, float Defence, float Speed, std::string GhPass, std::string IconPass, float ContainerAmount);
	~ShipParts();

	//船改造画面での描画関数
	void DrawParts(int X, int Y);

	//船改造画面でのアイコン描画
	void DrawPartsIcon(int X, int Y);

	//基本ステータス取得関数
	inline float* GetPartsStatus() {
		return basicStatus;
	}

	//パーツのステータス全てを一気に渡してみたい
	inline std::tuple<int, int, std::string, float*>GetAllPartsData() {
		return{ partsId, partsType, partsName, basicStatus };
	}

	//描画パーツ名の取得関数
	inline std::string& GetFactName() {
		return factName;
	}
	//修飾Modを取得する関数
	inline const std::vector<std::shared_ptr<Mod>>& GetPartsMod() {
		return myMods;
	}


	//修飾ステータスを含めたパーツのステータス取得
	inline float* GetTrueStatus() {
		return trueStatus;
	}
	//アイコン画像がクリックされたらtrueを返す関数
	bool isClicked(int MouseX, int MouseY);


	//パーツステータスを描画する
	void DrawPartsStatus(int TopX, int TopY);

	//パーツステータスと背景画像の描画
	void DrawPartsSet();

	//名前の文字列の長さを取得する関数
	inline int& GetStrLength() {
		return strWidth;
	}

	//装備状態を切り替える関数
	inline void	ChangeEquiped() {
		//装備していたら
		if (isEquiped)
		{
			//装備状態を外す
			isEquiped = false;
			return;
		}
		isEquiped = true;
	}


	//装備状況を返す関数
	inline bool IsEquiped() {
		return isEquiped;
	}

	//アイコン画像の描画中心を返す関数
	inline const tnl::Vector3& GetIconCenter() {
		return iconCenter;
	}

	//カーソルが上にある判定
	bool isCursored = false;

private:

	std::shared_ptr<Menu>statusBack = nullptr;

	std::shared_ptr<Menu>modNameBack = nullptr;

	//-------------基本ステータス-------------//
	const std::string STATUSNAME[5] = { "体力","電力","防御力","速度","貨物容量" };

	//パーツの追加体力
	float hp = 0;
	//パーツの必要電力
	float energy = 0;
	//パーツの追加防御力
	float defence = 0;
	//パーツの追加速度
	float speed = 0;
	//パーツの追加積載可能量
	float containerAmount = 0;

	//hp,energy,def,speed,container
	float basicStatus[5] = { 0,0,0,0,0 };

	//-----------------------------------------//

	//修飾ステータス合計を求める関数
	void SetEditStatus();
	//--------------修飾ステータス合計----------//
	//追加体力
	float addHp = 0;
	//必要電力
	float addEnergy = 0;
	//追加防御力
	float addDefence = 0;
	//追加速度
	float addSpeed = 0;
	//追加積載可能量
	float addContainerAmount = 0;

	//hp,energy,def,speed,container
	float addStatus[5] = { 0,0,0,0,0 };

	//--------------------------------------------//

	//船の合計ステータスを求める関数
	void SetTrueStatus();
	//船の合計ステータス
	float trueStatus[5] = {};

	//修飾ステータスを含めたパーツ名
	std::string factName = "";

	//名前の文字列の長さ
	int strWidth = 0;

	//所持修飾ステータス
	std::vector<std::shared_ptr<Mod>>myMods;


	//アイコン画像の描画中心座標
	int iconX = 0;
	int iconY = 0;

	tnl::Vector3 iconCenter = {};

	//アイコンマウス検知テスト画像
	int highRight = 0;

};
