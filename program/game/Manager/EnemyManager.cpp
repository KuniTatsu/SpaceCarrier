#include "EnemyManager.h"
#include"../Object/Enemy.h"

EnemyManager::EnemyManager()
{
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
