#include "Enemy.h"
#include"../StrategyPattern/MovementPattern.h"
#include"../StrategyPattern/ShootPattern.h"
#include"../Manager/GameManager.h"
#include"../Manager/EnemyManager.h"

Enemy::Enemy(tnl::Vector3 StartPos)
{
	tnl::DebugTrace("\n敵が生成されました\n");
	//画像読み込み
	gh = gManager->LoadGraphEx("graphics/Enemy.png");

	//初期座標決定
	pos = StartPos;
}

Enemy::Enemy(tnl::Vector3 StartPos, MovementBase* MoveType, ShootBase* ShootType)
{
	tnl::DebugTrace("\n敵が生成されました\n");

	//画像読み込み
	gh = gManager->LoadGraphEx("graphics/Enemy_2525.png");

	radius = 12.5;

	//初期座標決定
	pos = StartPos;

	//moveType = new StraightMove(vecSpeed);
	moveType = MoveType;
	shootType = ShootType;

	eManager = EnemyManager::Instance();
}

Enemy::~Enemy()
{
	tnl::DebugTrace("\n敵が消去されました\n");
	tnl::DebugTrace("\npos[%f,%f]\n",pos.x,pos.y);
}

void Enemy::Update()
{
	Move();
	shootType->Shoot(pos,radius,gManager->deltatime);
	CheckIsLive();
}

void Enemy::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, gh, true);
}

void Enemy::Init()
{
}

void Enemy::CheckIsLive()
{
	if (pos.y < -100 || pos.y>768 || pos.x < 0 || pos.x>1024) {
		isLive = false;
	}
}

void Enemy::SetEnemyList()
{
	eManager->AddEnemyList(std::dynamic_pointer_cast<Enemy, Object>(shared_from_this()));
}

void Enemy::Move()
{
	pos = moveType->Move(pos);
}
