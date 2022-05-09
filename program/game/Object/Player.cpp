#include "Player.h"
#include"../GameManager.h"

Player::Player()
{
	Init();
	tnl::DebugTrace("\nPlayerÇ™çÏê¨Ç≥ÇÍÇ‹ÇµÇΩ\n");

}

Player::~Player()
{
}

void Player::Update()
{
	Move();
}

void Player::Draw()
{
	gManager->DrawRotaGraphNormal(pos.x, pos.y, gh, true);
}

void Player::Init()
{
	pos = gManager->Center;
	gh = gManager->LoadGraphEx("graphics/Player.png");
}

void Player::Move()
{
	/*
	for (int i = 0; i < static_cast<int>(DIR::MAX); ++i) {
		if (tnl::Input::IsKeyDown(arrowKeys[i])) {
			
		}
	}
	*/

	moveX = 0;
	moveY = 0;

	//Ç«Ç§Ç…Ç©ÇµÇƒÇ‹Ç∆ÇﬂÇΩÇ¢Å@ä÷êîâªÇµÇΩÇ¢Ç™Ç§Ç‹Ç≠évÇ¢Ç¬Ç©Ç»Ç¢
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::UP)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::UP)];
	}
	else if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::DOWN)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::DOWN)];
	}

	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::RIGHT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::RIGHT)];
	}
	else if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::LEFT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::LEFT)];
	}

	if (moveX != 0 || moveY != 0) {
		tnl::Vector3 fixVec = GetFixVector(moveX, moveY);

		float fixMoveX = fixVec.x * SPEED;
		float fixMoveY = fixVec.y * SPEED;

		pos.x += fixMoveX;
		pos.y += fixMoveY;

	}
}
