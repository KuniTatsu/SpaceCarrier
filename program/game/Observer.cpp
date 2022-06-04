#include "Observer.h"
#include"Object/Enemy.h"
#include"Object/Player.h"
#include"Manager/GameManager.h"
#include"Manager/EnemyManager.h"

Observer::Observer()
{
	gManager = GameManager::Instance();
	player = gManager->GetPlayer();
}

Observer::~Observer()
{
}
//enemyが生成されたら呼ばれる関数
void Observer::Update(std::shared_ptr<Enemy> enemy)
{
	//haveTarget==true:ターゲットを持っているなら上書きしない
	if (player->haveTarget()) {
		return;
	}
	//生成されたエネミーをplayerのターゲット関数にぶちこむ
	player->SetMyTarget(enemy);
}

void Observer::DebugPlayer()
{
	if (player == nullptr) {
		DrawStringEx(600, 200, -1, "Playerが設定されていません");
	}
	else
	{
		DrawStringEx(600, 200, -1, "Playerが見つかりました");
	}
}
