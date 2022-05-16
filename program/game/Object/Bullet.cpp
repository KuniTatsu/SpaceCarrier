#include "Bullet.h"
#include"../GameManager.h"
#include"../Manager/BulletManager.h"
#include"../Movement/Movement.h"

Bullet::Bullet(tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	Initialize(StartPos, VPos);
	tnl::DebugTrace("\nBullet���쐬����܂���\n");
	bManager = BulletManager::Instance();
}
//�ړ��x�N�g�����w�肹���ɓ��������w�肷�鐶�����@
Bullet::Bullet(tnl::Vector3 StartPos, MovementBase* MoveType)
{
	Initialize(StartPos);
	tnl::DebugTrace("\nBullet���쐬����܂���\n");
	bManager = BulletManager::Instance();

	moveType = MoveType;

}

Bullet::~Bullet()
{
	tnl::DebugTrace("\nBullet���j������܂���\n");
}

void Bullet::Update()
{
	pos = moveType->Move(pos);
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
//�ړ��x�N�g���𒼐ڎw�肷�鐶�����@
void Bullet::Initialize(tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	gh = gManager->LoadGraphEx("graphics/bullet_5050.png");

	radius = 25;

	pos = StartPos;
	vPos = VPos;



}
//�ړ��x�N�g�����w�肹���ɓ��������w�肷�鐶�����@
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

}

void Bullet::SetBulletList()
{
	bManager->AddBulletList(std::dynamic_pointer_cast<Bullet, Object>(shared_from_this()));
}
