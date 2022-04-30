#include "Player.h"
#include"../GameManager.h"

Player::Player()
{
	Init();
	tnl::DebugTrace("\nPlayer���쐬����܂���\n");

}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Draw()
{
	gManager->DrawRotaGraphNormal(pos.x, pos.y, gh, true);
}

void Player::Init()
{
	gManager = GameManager::Instance();
	pos = gManager->Center;
	gh = gManager->LoadGraphEx("graphics/Player.png");
	//gManager->AddObjectList(shared_from_this());

	//gManager->test.emplace_back(this);
}
