#include "Enemy.h"
#include"../StrategyPattern/MovementPattern.h"
#include"../StrategyPattern/ShootPattern.h"
#include"../Manager/GameManager.h"
#include"../Manager/EnemyManager.h"
#include"../Observer.h"
#include"../Object/Bullet.h"

Enemy::Enemy(tnl::Vector3 StartPos)
{
	//tnl::DebugTrace("\n敵が生成されました\n");
	//画像読み込み
	gh = gManager->LoadGraphEx("graphics/Enemy.png");

	//初期座標決定
	pos = StartPos;
}

Enemy::Enemy(tnl::Vector3 StartPos, std::string Gh, MovementBase* MoveType, ShootBase* ShootType)
{
	//tnl::DebugTrace("\n敵が生成されました\n");

	//画像読み込み
	gh = gManager->LoadGraphEx(Gh);

	radius = 12.5;

	//初期座標決定
	pos = StartPos;

	//moveType = new StraightMove(vecSpeed);
	moveType = MoveType;
	shootType = ShootType;

	eManager = EnemyManager::Instance();
	//オブザーバ登録
	SetObserver(gManager->GetObserver());
}

Enemy::Enemy(tnl::Vector3 StartPos, std::string Gh, float Hp, float Attack, float Defence, float Speed, MovementBase* MoveType, ShootBase* ShootType)
{
	//tnl::DebugTrace("\n敵が生成されました\n");

	//画像読み込み
	gh = gManager->LoadGraphEx(Gh);

	radius = 12.5;

	//初期座標決定
	pos = StartPos;
	//-----ステータス決定-----//
	hp = Hp;
	attack = Attack;
	defence = Defence;
	speed = Speed;
	//------------------------//

	//moveType = new StraightMove(vecSpeed);
	moveType = MoveType;
	shootType = ShootType;

	//VecSpeedを取得
	vecSpeed = moveType->GetVecSpeed();

	eManager = EnemyManager::Instance();
	//オブザーバ登録
	SetObserver(gManager->GetObserver());
}

Enemy::Enemy(tnl::Vector3 StartPos, std::string Gh, float Hp, float Attack, float Defence, float Speed, MovementBase* MoveType, ShootBase* ShootType, ShootBase* ExShootType)
{
	//tnl::DebugTrace("\n敵が生成されました\n");

	//画像読み込み
	gh = gManager->LoadGraphEx(Gh);

	radius = 12.5;

	//初期座標決定
	pos = StartPos;
	//-----ステータス決定-----//
	hp = Hp;
	attack = Attack;
	defence = Defence;
	speed = Speed;
	//------------------------//

	//moveType = new StraightMove(vecSpeed);
	moveType = MoveType;
	shootType = ShootType;
	exShootType = ExShootType;

	eManager = EnemyManager::Instance();

	//オブザーバ登録
	SetObserver(gManager->GetObserver());
}

Enemy::~Enemy()
{
	//tnl::DebugTrace("\n敵が消去されました\n");
	//tnl::DebugTrace("\npos[%f,%f]\n", pos.x, pos.y);

	DeleteMemory();
}

void Enemy::Update()
{
	Move();
	shootType->CoolDawnUpdate(gManager->deltatime);
	auto bullet = shootType->Shoot(pos, radius, gManager->deltatime);

	if (bullet != nullptr)bullet->SetEnemyBulletList();
	CheckIsLive();
}

void Enemy::Draw()
{
	enemyChecker->DebugPlayer();
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

void Enemy::SetObserver(Observer* EnemyChecker)
{
	enemyChecker = EnemyChecker;
	//tnl::DebugTrace("\nObserverが登録されました\n");
}

void Enemy::notify()
{
	enemyChecker->Update(std::dynamic_pointer_cast<Enemy, Object>(shared_from_this()));
}

void Enemy::Move()
{
	pos = moveType->Move(pos);
}

void Enemy::DeleteMemory()
{
	delete moveType;
	delete shootType;
	//delete enemyChecker;
	if (exShootType != nullptr)delete exShootType;
}
