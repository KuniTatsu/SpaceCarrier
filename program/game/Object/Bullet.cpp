#include "Bullet.h"
#include"../GameManager.h"
#include"../Manager/BulletManager.h"

Bullet::Bullet(tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	Initialize(StartPos, VPos);
	tnl::DebugTrace("\nBullet‚ªì¬‚³‚ê‚Ü‚µ‚½\n");
	bManager = BulletManager::Instance();

}

Bullet::~Bullet()
{
	tnl::DebugTrace("\nBullet‚ª”jŠü‚³‚ê‚Ü‚µ‚½\n");
}

void Bullet::Update()
{
	pos += vPos;
	CheckIsLive();
}

void Bullet::Draw()
{
	DrawCircle(pos.x, pos.y, 10, -1, true);
}

void Bullet::Init()
{
}

void Bullet::Initialize(tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	gh = gManager->LoadGraphEx("graphics/Player");

	pos = StartPos;
	vPos = VPos;
	
}

void Bullet::CheckIsLive()
{
	if (pos.y < 0 || pos.y>768 || pos.x < 0 || pos.x>1024) {
		isLive = false;
	}

}
