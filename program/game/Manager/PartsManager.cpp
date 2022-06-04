#include "PartsManager.h"
#include"../ShipParts/PartsBase.h"
#include"../ShipParts/ShipParts.h"
#include"../ShipParts/WeaponParts.h"
#include<random>


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
	//---------------�D�̃p�[�c�̃��[�h-------------------------
	loadPartsCsv = tnl::LoadCsv("Csv/ShipPartsMaster.csv");
	for (int i = 1; i < loadPartsCsv.size(); ++i) {
		//id(int)	PartsType(int)	Parts_Name(string)	HP(float)	Atack(float)	Defence(float)	Speed(float)	Gh(std::string)	ContainerAmount

		int id = std::stoi(loadPartsCsv[i][0]);
		int type = std::stoi(loadPartsCsv[i][1]);

		float hp = std::stof(loadPartsCsv[i][3]);
		float energy = std::stof(loadPartsCsv[i][4]);
		float defence = std::stof(loadPartsCsv[i][5]);
		float speed = std::stof(loadPartsCsv[i][6]);

		float amount = std::stof(loadPartsCsv[i][9]);

		//auto parts = std::make_shared<ShipParts>(id, type, loadPartsCsv[i][2], hp, energy, defence, speed, loadPartsCsv[i][7], loadPartsCsv[i][8],amount);
		auto parts = std::make_shared<ShipParts>(id, type, loadPartsCsv[i][2], hp, energy, defence, speed, loadPartsCsv[i][7], loadPartsCsv[i][8], amount);
		shipPartsMaster[type].emplace_back(parts);

		PartsIdList.emplace_back(id);
	}

	//---------------����p�[�c�̃��[�h-------------------------

	loadWeaponPartsCsv = tnl::LoadCsv("Csv/WeaponPartsMaster.csv");
	for (int i = 1; i < loadWeaponPartsCsv.size(); ++i) {

		int id = std::stoi(loadWeaponPartsCsv[i][0]);
		int type = std::stoi(loadWeaponPartsCsv[i][1]);

		float attack = std::stof(loadWeaponPartsCsv[i][3]);
		float coolTime = std::stof(loadWeaponPartsCsv[i][4]);

		//int Id, int PartsType, std::string Name, float Attack, float CoolDawn, std::string ShootType, std::string GhPass);
		auto parts = std::make_shared<WeaponParts>(id, type, loadWeaponPartsCsv[i][2], attack, coolTime, loadWeaponPartsCsv[i][5], loadWeaponPartsCsv[i][6], loadWeaponPartsCsv[i][7]);
		weaponPartsMaster[type].emplace_back(parts);
	}


}

//�����p�[�c�������̔z��Ɋi�[����֐� �K��Ship.cpp����Ăяo������
void PartsManager::SetProtoTypeParts(std::vector<std::shared_ptr<PartsBase>>& PartsSet)
{
	//�����z��̑傫����5�����Ȃ珈�����Ȃ�
	if (PartsSet.size() < static_cast<uint32_t>(PARTSCODE::MAX))return;

	PartsSet[static_cast<uint32_t>(PARTSCODE::HULL)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::HULL)][0];
	PartsSet[static_cast<uint32_t>(PARTSCODE::CONTAINER)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::CONTAINER)][0];
	PartsSet[static_cast<uint32_t>(PARTSCODE::ARMOR)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::ARMOR)][0];
	PartsSet[static_cast<uint32_t>(PARTSCODE::GENERATOR)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::GENERATOR)][0];
	PartsSet[static_cast<uint32_t>(PARTSCODE::THRUSTER)] = shipPartsMaster[static_cast<uint32_t>(PARTSCODE::THRUSTER)][0];

}

void PartsManager::SetProtoTypeWeapon(std::vector<std::shared_ptr<PartsBase>>& WeaponSet)
{
	WeaponSet.emplace_back(weaponPartsMaster[0][0]);
	WeaponSet.emplace_back(weaponPartsMaster[1][1]);
}

std::shared_ptr<PartsBase> PartsManager::GetParts(int PartsId)
{
	std::shared_ptr<ShipParts> selectParts = nullptr;
	//�p�[�cId������
	for (auto type : shipPartsMaster) {
		for (auto parts : type) {
			//id����v������
			if (parts->GetPartsId() == PartsId) {
				selectParts = parts;
				break;
			}
		}
	}

	//�p�[�c�f�[�^�擾

	auto [id, type, name, basicStatus] = selectParts->GetAllPartsData();
	/*int id = selectParts->GetPartsId();
	int type = selectParts->GetPartsType();*/

	//std::string name = selectParts->GetPartsName();
	auto pass = selectParts->GetPartsGhPass();
	auto icon = selectParts->GetIconGhPass();

	//float* basicStatus = {};
	//basicStatus = selectParts->GetPartsStatus();

	//�V�K����
	auto newParts = std::make_shared<ShipParts>(id, type, name, basicStatus[0], basicStatus[1], basicStatus[2], basicStatus[3], pass, icon, basicStatus[4]);

	return newParts;
}

std::shared_ptr<PartsBase> PartsManager::GetWeaponParts(int PartsId)
{
	std::shared_ptr<WeaponParts> selectParts = nullptr;
	//�p�[�cId������
	for (auto type : weaponPartsMaster) {
		for (auto parts : type) {
			//id����v������
			if (parts->GetPartsId() == PartsId) {
				selectParts = parts;
				break;
			}
		}
	}

	//�f�[�^�擾

	auto [id, type, name, attack, coolDown, myShoot, ghPass] = selectParts->GetAllWeaponData();

	auto icon = selectParts->GetIconGhPass();
	//�V�K����
	////id(int)	PartsType(int)	Parts_Name	Atack(int)	CoolDawn(float)	BulletType(enum) Gh(std::string)
	auto newWeapon = std::make_shared<WeaponParts>(id, type, name, attack, coolDown, myShoot, ghPass, icon);
	return newWeapon;
}

std::shared_ptr<PartsBase> PartsManager::GetRandomParts()
{
	auto rand = GetRandomPartsId();

	return GetParts(rand);
}

int PartsManager::GetRandomPartsId()
{
	// �񌈒�I�ȗ���������->�����V�[�h�Ɏg��
	std::random_device rnd;
	//�����_���Ȑ������߂邽�߂̊֐��������߂�
	 // �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
	std::mt19937 GetRandom(rnd());

	//���͈͂̈�l���z�����擾
	std::uniform_int_distribution<> Weight(0, PartsIdList.size() - 1);
	//���A���e�B�������_���Ō��߂�
	int rand = Weight(GetRandom);

	return PartsIdList[rand];
}
