#pragma once
#include"PartsBase.h"

class ShipParts :public PartsBase
{
public:
	//id(int)	PartsType(int)	Parts_Name	HP(float)	Atack(float)	Defence(float)	Speed(float)	Gh(std::string)	ContainerAmount
	ShipParts(int Id, int PartsType, std::string Name, float Hp, float Energy, float Defence, float Speed, std::string GhPass, float ContainerAmount);
	~ShipParts();

	//船改造画面での描画関数
	void DrawParts(int X, int Y);

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

	//hp,energy,def,speed
	float basicStatus[4] = {};

};
