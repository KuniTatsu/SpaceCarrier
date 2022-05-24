#include "PartsManager.h"
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
		float attack = std::stof(loadPartsCsv[i][4]);
		float defence = std::stof(loadPartsCsv[i][5]);
		float speed = std::stof(loadPartsCsv[i][6]);

		float amount = std::stof(loadPartsCsv[i][8]);


		auto parts = std::make_shared<ShipParts>(id, type, loadPartsCsv[i][2], hp, attack, defence, speed, loadPartsCsv[i][7], amount);
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
