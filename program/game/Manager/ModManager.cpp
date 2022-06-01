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
	//----------------Mod�}�X�^�[�V�[�g�̓ǂݍ���----------------------//
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

	//----------------���A���e�B�E�F�C�gcsv�̓ǂݍ���----------------------//
	auto loadRarityCsv = tnl::LoadCsv("Csv/ModRarityWeight.csv");

	for (int i = 1; i < static_cast<uint32_t>(RARITY::MAX) + 1; ++i) {
		rarityWeight[i - 1] = stoi(loadRarityCsv[i][1]);
	}

	//----------------ModWeightCsv�ǂݍ���-------------------------//

	auto loadModWeightCsv = tnl::LoadCsv("Csv/ModWeight.csv");
	for (int i = 1; i < loadModWeightCsv.size(); ++i) {
		modWeight.emplace_back(stoi(loadModWeightCsv[i][3]));
	}

}

std::unique_ptr<Mod> ModManager::GetRandomMod()
{
	//-------------���A���e�B����------------------//

	// �񌈒�I�ȗ���������->�����V�[�h�Ɏg��
	std::random_device rnd;
	//�����_���Ȑ������߂邽�߂̊֐��������߂�
	 // �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
	std::mt19937 GetRandom(rnd());

	//���A���e�B�����肷��
	int rarityTotalWeight = 0;

	int selectedRarity = 0;

	//totalWeight�����߂�->������Level�ɂ���ďo������A�C�e����ω������A���̏�ō�����A�C�e�����X�g��weight�Ōv�Z����悤�ɂ���
	for (int i = 0; i < static_cast<uint32_t>(RARITY::MAX) + 1; ++i) {
		rarityTotalWeight += rarityWeight[i];
	}
	//���͈͂̈�l���z�����擾
	std::uniform_int_distribution<> Weight(0, rarityTotalWeight);
	//���A���e�B�������_���Ō��߂�
	int rand = Weight(GetRandom);

	//���I
	for (int i = 0; i < static_cast<uint32_t>(RARITY::MAX) + 1; i++) {
		if (rand < rarityWeight[i]) {
			//�A�C�e������
			selectedRarity = i;
			break;
		}

		// ���̑Ώۂ𒲂ׂ�
		rand -= rarityWeight[i];
	}

	//-------------Mod����------------------//




	return std::unique_ptr<Mod>();
}
