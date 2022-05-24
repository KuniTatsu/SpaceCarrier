#include "Bullet.h"
#include"../Manager/GameManager.h"
#include"../Manager/BulletManager.h"
#include"../StrategyPattern/MovementPattern.h"

Bullet::Bullet(tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	Initialize(StartPos, VPos);
	tnl::DebugTrace("\nBulletが作成されました\n");
	bManager = BulletManager::Instance();
}
//移動ベクトルを指定せずに動き方を指定する生成方法
Bullet::Bullet(tnl::Vector3 StartPos, MovementBase* MoveType)
{
	Initialize(StartPos);
	tnl::DebugTrace("\nBulletが作成されました\n");
	bManager = BulletManager::Instance();

	moveType = MoveType;

	/*tnl::Vector3 vecSpeed = moveType->GetVecSpeed();

	tnl::DebugTrace("\n%d,%d,%d\n", vecSpeed.x, vecSpeed.y, vecSpeed.z);*/

}

Bullet::~Bullet()
{
	tnl::DebugTrace("\nBulletが破棄されました\n");
}

void Bullet::Update()
{
	pos = moveType->Move(pos);
	liveTime += gManager->deltatime;
	
	CheckIsLive();
}

void Bullet::Draw()
{
	//DrawCircle(pos.x, pos.y, 10, -1, true);
	DrawRotaGraph(pos.x, pos.y, 0.5, 0, gh, true);
}

void Bullet::Init()
{
}
//移動ベクトルを直接指定する生成方法
void Bullet::Initialize(tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	gh = gManager->LoadGraphEx("graphics/bullet_5050.png");

	radius = 25;

	pos = StartPos;
	vPos = VPos;



}
//移動ベクトルを指定せずに動き方を指定する生成方法
void Bullet::Initialize(tnl::Vector3& StartPos)
{
	gh = gManager->LoadGraphEx("graphics/bullet_5050.png");

	radius = 25;

	pos = StartPos;
}

void Bullet::CheckIsLive()
{
	if (pos.y < 0 || pos.y>768 || pos.x < 0 || pos.x>1024) {
		isLive = false;
	}
	if (liveTime > MAXLIVETIME)isLive = false;

}

void Bullet::SetBulletList()
{
	bManager->AddBulletList(std::dynamic_pointer_cast<Bullet, Object>(shared_from_this()));
}

void Bullet::SetEnemyBulletList()
{
	bManager->AddEnemyBulletList(std::dynamic_pointer_cast<Bullet, Object>(shared_from_this()));
}
