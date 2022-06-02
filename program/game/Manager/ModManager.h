#pragma once
#include<vector>
#include<string>
#include<memory>

class Mod;
class GameManager;

class ModManager
{
public:
	//インスタンスがなければ生成、あれば返す関数
	static ModManager* Instance();

	//初期化
	void Init();

	//ウェイトから付与するmodを決定するランダム関数
	std::unique_ptr<Mod>& GetRandomMod();

	//ModIDから付与するmodを返す関数
	std::unique_ptr<Mod>& GetModFromId(int Id);

	//Modを新しく生成して返す関数
	std::shared_ptr<Mod>CreateNewMod();

protected:
	ModManager();
	~ModManager();

private:
	//シングルトンインスタンス
	static ModManager* instance;

	//ゲームマネージャインスタンス
	GameManager* gManager = nullptr;


	//ダミー用Mod
	std::unique_ptr<Mod> dummyMod = nullptr;

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

	//gamemanagerのランダム関数を使うにはvectorのほうが都合がいい
	std::vector<int>rarityWeightList;

	//Modのウェイト
	//std::vector<int>modWeight;
	std::vector < std::vector<int>> modWeightList;

	



};

