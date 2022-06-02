//***ShipPartsに付く修飾Modのクラス***
//パーツ名に名前が追加される+能力値が追加される
#pragma once
#include<string>
#include<tuple>

class Mod
{
public:
	Mod() {};
	Mod(int Id,int Type,std::string Name,float Hp,float Energy,float Defence,float Speed,float Container);
	~Mod();

	//float型の基本ステータス取得関数
	inline float* GetBasicStatus() {
		return basicStatus;
	}
	//Mod名取得関数
	std::string GetModName() {
		return modName;
	}

	//ModId取得関数
	inline int& GetModId() {
		return modId;
	}

	//Modインスタンス生成に必要なデータ全てを渡す関数
	inline std::tuple<int, int, std::string, float*>GetModData() {
		return { modId,modType,modName,basicStatus };
	}

private:
	//id
	int modId = 0;
	//type
	int modType = 0;
	//name
	std::string modName = "";


	//追加体力
	float hp = 0;
	//必要電力
	float energy = 0;
	//追加防御力
	float defence = 0;
	//追加速度
	float speed = 0;
	//追加積載可能量
	float containerAmount = 0;

	//hp,energy,def,speed,container
	float basicStatus[5] = {};

};

