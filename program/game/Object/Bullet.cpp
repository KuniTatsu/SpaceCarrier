#include "Bullet.h"
#include"../GameManager.h"

Bullet::Bullet()
{
	Init();
	tnl::DebugTrace("\nBullet���쐬����܂���\n");
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
