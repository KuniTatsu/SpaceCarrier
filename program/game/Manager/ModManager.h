#pragma once
#include<vector>
#include<string>
#include<memory>

class Mod;

class ModManager
{
public:
	//インスタンスがなければ生成、あれば返す関数
	static ModManager* Instance();

	//初期化
	void Init();

	//ウェイトから付与するmodを決定するランダム関数
	std::unique_ptr<Mod>& GetRandomMod();
protected:
	ModManager();
	~ModManager();

private:
	//シングルトンインスタンス
	static ModManager* instance;

	//レアリティ
	enum class RARITY :uint32_t {
		JUNK,
		NORMAL,
		RARE,
		LEGEND,
		MAX
	};

	//csvロード関数
	void LoadModCsv();

	//csvから読み込んだ生データ
	std::vector<std::vector<std::string>>loadMods;
	//レアリティごとに分けられたマスターデータ
	std::vector < std::vector<std::unique_ptr<Mod>>>modMaster;

	//レアリティのウェイト
	int rarityWeight[static_cast<uint32_t>(RARITY::MAX)];

	//Modのウェイト
	std::vector<int>modWeight;




};

