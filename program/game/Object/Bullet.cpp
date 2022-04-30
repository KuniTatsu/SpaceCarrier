#include "Bullet.h"
#include"../GameManager.h"

Bullet::Bullet()
{
	Init();
	tnl::DebugTrace("\nBulletが作成されました\n");
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
}

void Bullet::Draw()
{
}

void Bullet::Init()
{
	gManager = GameManager::Instance();
	gh = gManager->LoadGraphEx("graphics/Player");
}
