#include <time.h>
#include <list>
#include <map>
#include <algorithm>
#include "game_main.h"
#include"Manager/GameManager.h"
#include"Manager/BulletManager.h"
#include"Manager/EnemyManager.h"
#include"Manager/PartsManager.h"
#include"Manager/ModManager.h"
#include "../dxlib_ext/dxlib_ext.h"

bool init = false;

GameManager* GameManager::instance = nullptr;
BulletManager* BulletManager::instance = nullptr;
EnemyManager* EnemyManager::instance = nullptr;
PartsManager* PartsManager::instance = nullptr;
ModManager* ModManager::instance = nullptr;

GameManager* gManager = nullptr;

void gameMain(float delta_time) {

	if (!init) {
		gManager = GameManager::Instance();

		gManager->initGameManager();
		init = true;
	}

	gManager->Update(delta_time);
	gManager->Draw(delta_time);

	/*if (tnl::Input::IsKeyDown(eKeys::KB_UP)) {
		DrawStringEx(100, 50, -1, "up");
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
		DrawStringEx(100, 70, -1, "left");
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)) {
		DrawStringEx(100, 90, -1, "space");
	}*/

}

