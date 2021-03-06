#include "ModManager.h"
#include"../Mod.h"
#include"../../dxlib_ext/dxlib_ext.h"
#include<random>
#include"GameManager.h"

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
	gManager = GameManager::Instance();
	LoadModCsv();
	//範囲外用returnのためのダミー作成
	dummyMod = make_unique<Mod>();
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
		rarityWeightList.emplace_back(stoi(loadRarityCsv[i][1]));
	}

	//----------------ModWeightCsv読み込み-------------------------//

	auto loadModWeightCsv = tnl::LoadCsv("Csv/ModWeight.csv");

	modWeightList.resize(static_cast<uint32_t>(RARITY::MAX));
	/*for (int i = 1; i < loadModWeightCsv.size(); ++i) {
		modWeight.emplace_back(stoi(loadModWeightCsv[i][3]));
	}*/

	for (int i = 1; i < loadModWeightCsv.size(); ++i) {

		int rarity = stoi(loadModWeightCsv[i][1]);
		modWeightList[rarity].emplace_back(stoi(loadModWeightCsv[i][3]));
	}

	//test
	//GetRandomMod();
}

std::unique_ptr<Mod>& ModManager::GetRandomMod()
{
	//-------------レアリティ決定------------------//

	int rarity = gManager->GerRandomNumInWeight(rarityWeightList);
	//--------------Mod決定------------------------//
	int mod = gManager->GerRandomNumInWeight(modWeightList[rarity]);


	return modMaster[rarity][mod];
	/*

	// 非決定的な乱数生成器->初期シードに使う
	std::random_device rnd;
	//ランダムな数を求めるための関数名を決める
	 // メルセンヌ・ツイスタの32ビット版、引数は初期シード
	std::mt19937 GetRandom(rnd());

	//レアリティを決定する
	int rarityTotalWeight = 0;
	int selectedRarity = 0;

	//totalWeightを求める
	for (int i = 0; i < static_cast<uint32_t>(RARITY::MAX); ++i) {
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

	int modTotalWeight = 0;
	int selectedMod = 0;

	for (int i = 0; i < modWeight.size(); ++i) {
		modTotalWeight += modWeight[i];
	}
	//一定範囲の一様分布乱数取得
	std::uniform_int_distribution<> ModWeight(0, rarityTotalWeight);
	//Modをランダムで決める
	int modRand = ModWeight(GetRandom);

	//抽選
	for (int i = 0; i < modWeight.size(); i++) {
		if (modRand < modWeight[i]) {
			//アイテム決定
			selectedMod = i;
			break;
		}

		// 次の対象を調べる
		modRand -= modWeight[i];
	}

	*/

	//return modMaster[selectedRarity][selectedMod];
}

std::unique_ptr<Mod>& ModManager::GetModFromId(int Id)
{
	for (int i = 0; i < modMaster.size(); ++i) {
		for (int k = 0; k < modMaster[i].size(); ++k) {
			if (Id == modMaster[i][k]->GetModId()) {
				return modMaster[i][k];
			}
		}
	}

	tnl::WarningMassage("適切なModIdではありません");
	return dummyMod;
}

std::shared_ptr<Mod> ModManager::CreateNewMod()
{
	//auto [id, type, name, basicStatus] = modData->GetModData();
	auto [id, type, name, basicStatus] = GetRandomMod()->GetModData();

	auto newMod = std::make_shared<Mod>(id, type, name, basicStatus[0], basicStatus[1], basicStatus[2], basicStatus[3], basicStatus[4]);
	return newMod;
}
