#include "Player.h"
#include"../GameManager.h"
#include"Bullet.h"
#include"../Factory.h"

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
	//�ړ�
	Move();

	//�e���˃^�C�}�[�X�V
	shootTimer += gManager->deltatime;
}

void Player::Draw()
{
	gManager->DrawRotaGraphNormal(pos.x, pos.y, gh, true);
}

void Player::Init()
{
	pos = gManager->Center;
	gh = gManager->LoadGraphEx("graphics/Player_5050.png");
	fac = gManager->GetFactory();
}

void Player::CheckIsLive()
{
}

void Player::Move()
{
	/*
	for (int i = 0; i < static_cast<int>(DIR::MAX); ++i) {
		if (tnl::Input::IsKeyDown(arrowKeys[i])) {

		}
	}
	*/
	//�ړ��ʃ��Z�b�g
	moveX = 0;
	moveY = 0;

	//�ǂ��ɂ����Ă܂Ƃ߂����@�֐��������������܂��v�����Ȃ�
	//�㉺�L�[���m
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::UP)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::UP)];
	}
	else if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::DOWN)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::DOWN)];
	}

	//���E�L�[���m
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::RIGHT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::RIGHT)];
	}
	else if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::LEFT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::LEFT)];
	}

	//�ړ��ʂ�0�łȂ���΃x�N�g���𐳋K�����Ĉړ�������
	if (moveX != 0 || moveY != 0) {
		tnl::Vector3 fixVec = GetFixVector(moveX, moveY);

		float fixMoveX = fixVec.x * SPEED;
		float fixMoveY = fixVec.y * SPEED;

		pos.x += fixMoveX;
		pos.y += fixMoveY;

	}
}

void Player::ShootBullet()
{
	//�N�[���_�E�����Ȃ甭�˂��Ȃ�
	if (shootTimer < SHOOTCOOLDOWN)return;
	//�N�[���_�E���Z�b�g
	shootTimer = 0;

	//���x�x�N�g���Z�b�g
	tnl::Vector3 vec = { 0,-10,0 };

	tnl::DebugTrace("\n%d,%d,%d\n", pos.x, pos.y, pos.z);

	//�e�̐���
	auto bullet = fac->create("Bullet", pos, vec);;
	bullet->SetList();

}
