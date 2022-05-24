#include "EnemyManager.h"
#include"../Object/Enemy.h"
#include"../Factory.h"
#include"GameManager.h"
#include"../StrategyPattern/MovementPattern.h"
#include"../StrategyPattern/ShootPattern.h"
#include"../EnemyData.h"

EnemyManager::EnemyManager()
{
	gManager = GameManager::Instance();
	fac = gManager->GetFactory();
	LoadEnemyMaster();
}

EnemyManager::~EnemyManager()
{
}

EnemyManager* EnemyManager::Instance()
{
	if (instance == nullptr) {
		instance = new EnemyManager();
	}
	return instance;
}

void EnemyManager::RemoveEnemyList()
{
	auto it = liveEnemy.begin();
	while (it != liveEnemy.end()) {
		if (!(*it)->GetIsLive()) {
			it = liveEnemy.erase(it);
			continue;
		}
		it++;
	}
}

std::shared_ptr<Enemy> EnemyManager::CreateEnemy(ENEMYTYPE Type, tnl::Vector3 StartPos, tnl::Vector3 VPos)
{
	if (Type == ENEMYTYPE::NORMAL) {
		//�����factory�œǂݎ�肽��
		//auto enemy = GetRandomEnemyData(static_cast<int>(Type));
		return std::dynamic_pointer_cast<Enemy, Object>(fac->create("Enemy", StartPos, VPos, Factory::ENEMYTYPE::NORMAL));
	}
	return std::shared_ptr<Enemy>();
}

void EnemyManager::LoadEnemyMaster()
{
	loadEnemy = tnl::LoadCsv("Csv/EnemyMaster.csv");

	enemyMaster.resize(3);

	//id(int)	EnemyType(int)	Enemy_Name(string)	HP(int)	Atack(int)	Defence(int)	Speed(int)	Gh(std::string)	
					//MoveType(string)ShootType(string) ExShootType	Exp(int)	

	for (int i = 1; i < loadEnemy.size(); ++i) {
		//id
		int id = std::stoi(loadEnemy[i][0]);
		//EnemyType
		int type = std::stoi(loadEnemy[i][1]);
		//HP
		float hp = std::stof(loadEnemy[i][3]);
		//Attack
		float attack = std::stof(loadEnemy[i][4]);
		//Defence
		float defence = std::stof(loadEnemy[i][5]);
		//Speed
		float speed = std::stof(loadEnemy[i][6]);


		//----------�ړ����@�̌���------------//
		Factory::MOVETYPE move;
		if (loadEnemy[i][8] == "STRAIGHT") {
			//�ォ��ύX����̂ŉ��̒l
			move = Factory::MOVETYPE::STRAIGHT;
		}
		else if (loadEnemy[i][8] == "SLIDE") {
			//�ォ��ύX����̂ŉ��̒l
			move = Factory::MOVETYPE::SLIDE;
		}
		else if (loadEnemy[i][8] == "FARSTOP") {
			//�ォ��ύX����̂ŉ��̒l
			move = Factory::MOVETYPE::FARSTOP;
		}
		else if (loadEnemy[i][8] == "MIDDLESTOP") {
			//VPos�͌ォ��ύX����̂ŉ��̒l
			move = Factory::MOVETYPE::MIDDLESTOP;
		}
		//------------------------------------//

		//----------�ˌ����@�̌���------------//
		Factory::SHOOTTYPE shoot;
		Factory::SHOOTTYPE exShoot;
		if (loadEnemy[i][9] == "STRAIGHT") {
			//�ォ��ύX����̂ŉ��̒l
			shoot = Factory::SHOOTTYPE::STRAIGHT;
		}
		else if (loadEnemy[i][9] == "FOCUS") {
			//�ォ��ύX����̂ŉ��̒l
			shoot = Factory::SHOOTTYPE::FOCUS;
		}
		else if (loadEnemy[i][9] == "FASTSHOT") {
			//�ォ��ύX����̂ŉ��̒l
			shoot = Factory::SHOOTTYPE::FAST;
		}
		//---exShoot---

		if (loadEnemy[i][10] == "NONE") {
			//�Ȃ�
			exShoot = Factory::SHOOTTYPE::NONE;
		}
		else if (loadEnemy[i][10] == "STRAIGHT") {
			//�ォ��ύX����̂ŉ��̒l
			exShoot = Factory::SHOOTTYPE::STRAIGHT;
		}
		else if (loadEnemy[i][10] == "FOCUS") {
			//�ォ��ύX����̂ŉ��̒l
			exShoot =Factory::SHOOTTYPE::FOCUS;
		}
		else if (loadEnemy[i][10] == "FASTSHOT") {
			//�ォ��ύX����̂ŉ��̒l
			exShoot =Factory::SHOOTTYPE::FAST;
		}

		auto masterEnemy = std::make_shared<EnemyData>(id, type, loadEnemy[i][2], hp, attack, defence, speed, loadEnemy[i][7], move, shoot, exShoot);
		enemyMaster[type].emplace_back(masterEnemy);
	}


}

std::shared_ptr<EnemyData> EnemyManager::GetRandomEnemyData(int EnemyType)
{
	int num = enemyMaster[EnemyType].size();

	int random = GetRand(10000) % num;

	return enemyMaster[EnemyType][random];
}
