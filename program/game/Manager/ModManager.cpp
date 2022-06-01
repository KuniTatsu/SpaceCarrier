#include "ModManager.h"
#include"../Mod.h"
#include"../../dxlib_ext/dxlib_ext.h"
#include<random>

using namespace std;

ModManager* ModManager::Instance()
{
	if (instance == nullptr) {
		instance = new ModManager();
	}
	return instance;
}

void ModManager::Init()
{
	LoadModCsv();
}

ModManager::ModManager()
{
	Init();
}

ModManager::~ModManager()
{
}

void ModManager::LoadModCsv()
{
	//----------------Modマスターシートの読み込み----------------------//
	loadMods = tnl::LoadCsv("Csv/ModsMaster.csv");

	modMaster.resize(static_cast<uint32_t>(RARITY::MAX));

	//id(int)	ModType(int)	Mod_Name	HP(float)	Energy(float)	Defence(float)	Speed(float)	ContainerAmount
	for (int i = 1; i < loadMods.size(); ++i) {

		int id = stoi(loadMods[i][0]);
		int type = stoi(loadMods[i][1]);

		float hp = stof(loadMods[i][3]);
		float energy = stof(loadMods[i][4]);
		float defence = stof(loadMods[i][5]);
		float speed = stof(loadMods[i][6]);
		float container = stof(loadMods[i][7]);

		auto mod = make_unique<Mod>(id, type, loadMods[i][2], hp, energy, defence, speed, container);

		modMaster[type].emplace_back(std::move(mod));
	}

	//----------------レアリティウェイトcsvの読み込み----------------------//
	auto loadRarityCsv = tnl::LoadCsv("Csv/ModRarityWeight.csv");

	for (int i = 1; i < static_cast<uint32_t>(RARITY::MAX) + 1; ++i) {
		rarityWeight[i - 1] = stoi(loadRarityCsv[i][1]);
	}

	//----------------ModWeightCsv読み込み-------------------------//

	auto loadModWeightCsv = tnl::LoadCsv("Csv/ModWeight.csv");
	for (int i = 1; i < loadModWeightCsv.size(); ++i) {
		modWeight.emplace_back(stoi(loadModWeightCsv[i][3]));
	}

}

std::unique_ptr<Mod> ModManager::GetRandomMod()
{
	//-------------レアリティ決定------------------//

	// 非決定的な乱数生成器->初期シードに使う
	std::random_device rnd;
	//ランダムな数を求めるための関数名を決める
	 // メルセンヌ・ツイスタの32ビット版、引数は初期シード
	std::mt19937 GetRandom(rnd());

	//レアリティを決定する
	int rarityTotalWeight = 0;

	int selectedRarity = 0;

	//totalWeightを求める->いずれLevelによって出現するアイテムを変化させ、その場で作ったアイテムリストのweightで計算するようにする
	for (int i = 0; i < static_cast<uint32_t>(RARITY::MAX) + 1; ++i) {
		rarityTotalWeight += rarityWeight[i];
	}
	//一定範囲の一様分布乱数取得
	std::uniform_int_distribution<> Weight(0, rarityTotalWeight);
	//レアリティをランダムで決める
	int rand = Weight(GetRandom);

	//抽選
	for (int i = 0; i < static_cast<uint32_t>(RARITY::MAX) + 1; i++) {
		if (rand < rarityWeight[i]) {
			//アイテム決定
			selectedRarity = i;
			break;
		}

		// 次の対象を調べる
		rand -= rarityWeight[i];
	}

	//-------------Mod決定------------------//




	return std::unique_ptr<Mod>();
}
