#include "PartsManager.h"
#include"../ShipParts/PartsBase.h"
#include"../ShipParts/ShipParts.h"
#include"../ShipParts/WeaponParts.h"


PartsManager::PartsManager()
{
	Init();
}

PartsManager::~PartsManager()
{
}

PartsManager* PartsManager::Instance()
{
	if (instance == nullptr) {
		instance = new PartsManager();
	}
	return instance;
}

void PartsManager::Init()
{
	shipPartsMaster.resize(5);
	weaponPartsMaster.resize(2);

	LoadCsv();
}

void PartsManager::LoadCsv()
{
	//---------------船体パーツのロード-------------------------
	loadPartsCsv = tnl::LoadCsv("Csv/ShipPartsMaster.csv");
	for (int i = 1; i < loadPartsCsv.size(); ++i) {
		//id(int)	PartsType(int)	Parts_Name(string)	HP(float)	Atack(float)	Defence(float)	Speed(float)	Gh(std::string)	ContainerAmount

		int id = std::stoi(loadPartsCsv[i][0]);
		int type = std::stoi(loadPartsCsv[i][1]);

		float hp = std::stof(loadPartsCsv[i][3]);
		float energy = std::stof(loadPartsCsv[i][4]);
		float defence = std::stof(loadPartsCsv[i][5]);
		float speed = std::stof(loadPartsCsv[i][6]);

		float amount = std::stof(loadPartsCsv[i][8]);


		auto parts = std::make_shared<ShipParts>(id, type, loadPartsCsv[i][2], hp, energy, defence, speed, loadPartsCsv[i][7], amount);
		shipPartsMaster[type].emplace_back(parts);
	}

	//---------------武器パーツのロード-------------------------

	loadWeaponPartsCsv = tnl::LoadCsv("Csv/WeaponPartsMaster.csv");
	for (int i = 1; i < loadWeaponPartsCsv.size(); ++i) {

		int id = std::stoi(loadWeaponPartsCsv[i][0]);
		int type = std::stoi(loadWeaponPartsCsv[i][1]);

		float attack = std::stof(loadWeaponPartsCsv[i][3]);
		float coolTime = std::stof(loadWeaponPartsCsv[i][4]);

		//int Id, int PartsType, std::string Name, float Attack, float CoolDawn, std::string ShootType, std::string GhPass);
		auto parts = std::make_shared<WeaponParts>(id, type, loadWeaponPartsCsv[i][2], attack, coolTime, loadWeaponPartsCsv[i][5], loadWeaponPartsCsv[i][6]);
		weaponPartsMaster[type].emplace_back(parts);
	}


}

//初期パーツを引数の配列に格納する関数 必ずShip.cppから呼び出すこと
void PartsManager::SetProtoTypeParts(std::vector<std::shared_ptr<PartsBase>>& PartsSet)
{
	//入れる配列の大きさが5未満なら処理しない
	if (PartsSet.size() < static_cast<uint32_t>(PARTSCODE::MAX))return;

	PartsSet[static_cast<uint32_t>(PARTSCODE::HULL)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::HULL)][0];
	PartsSet[static_cast<uint32_t>(PARTSCODE::CONTAINER)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::CONTAINER)][0];
	PartsSet[static_cast<uint32_t>(PARTSCODE::ARMOR)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::ARMOR)][0];
	PartsSet[static_cast<uint32_t>(PARTSCODE::GENERATOR)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::GENERATOR)][0];
	PartsSet[static_cast<uint32_t>(PARTSCODE::THRUSTER)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::THRUSTER)][0];

}
