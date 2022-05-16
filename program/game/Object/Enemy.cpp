#include "Enemy.h"
#include"../Movement/Movement.h"
#include"../GameManager.h"
#include"../Manager/EnemyManager.h"

Enemy::Enemy(tnl::Vector3 StartPos)
{
	tnl::DebugTrace("\n�G����������܂���\n");
	//�摜�ǂݍ���
	gh = gManager->LoadGraphEx("graphics/Enemy.png");

	//�������W����
	pos = StartPos;
}

Enemy::Enemy(tnl::Vector3 StartPos, MovementBase* MoveType)
{
	tnl::DebugTrace("\n�G����������܂���\n");

	//�摜�ǂݍ���
	gh = gManager->LoadGraphEx("graphics/Enemy.png");

	radius = 25;

	//�������W����
	pos = StartPos;

	//moveType = new StraightMove(vecSpeed);
	moveType = MoveType;

	eManager = EnemyManager::Instance();
}

Enemy::~Enemy()
{
	tnl::DebugTrace("\n�G����������܂���\n");
}

void Enemy::Update()
{
	Move();
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
