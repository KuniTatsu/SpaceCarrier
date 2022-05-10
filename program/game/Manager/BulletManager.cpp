#include "BulletManager.h"
#include"../Object/Bullet.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{

}

BulletManager* BulletManager::Instance()
{
	if (instance == nullptr) {
		instance = new BulletManager();
	}
	return instance;
}

void BulletManager::RemoveBulletList()
{
	auto it = liveBullet.begin();
	while (it != liveBullet.end()) {
		if (!(*it)->GetIsLive()) {
			it = liveBullet.erase(it);
			continue;
		}
		it++;
	}
}


