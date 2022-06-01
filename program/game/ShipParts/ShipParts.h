#pragma once
#include<vector>
#include<memory>
#include<tuple>
#include"PartsBase.h"

class Mod;

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
	inline std::tuple<int, int, std::string,float*>GetAllPartsData() {
		return{ partsId, partsType, partsName, basicStatus };
	}

private:
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
	float basicStatus[5] = {};


	//所持修飾ステータス
	std::vector<std::shared_ptr<Mod>>myMods;

};
