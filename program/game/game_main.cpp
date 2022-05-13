#include <time.h>
#include <list>
#include <map>
#include <algorithm>
#include "game_main.h"
#include"GameManager.h"
#include"Manager/BulletManager.h"
#include "../dxlib_ext/dxlib_ext.h"

bool init = false;

GameManager* GameManager::instance = nullptr;
BulletManager* BulletManager::instance = nullptr;

GameManager* gManager = nullptr;

void gameMain(float delta_time) {

	if (!init) {
		gManager = GameManager::Instance();

		gManager->initGameManager();
		init = true;
	}

	gManager->Update(delta_time);
	gManager->Draw(delta_time);

}

