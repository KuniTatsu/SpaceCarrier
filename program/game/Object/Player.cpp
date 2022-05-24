#include "Player.h"
#include"../Manager/GameManager.h"
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

	missileTimer += gManager->deltatime;
}

void Player::Draw()
{
	gManager->DrawRotaGraphNormal(pos.x, pos.y, gh, true);
	if (autoTargetMode) {
		DrawStringEx(200, 200, -1, "�I�[�g�^�[�Q�b�gON");
		//�^�[�Q�b�g�T�[�N���`��
		if (myTarget == nullptr)return;
		DrawRotaGraph(myTarget->GetPos().x, myTarget->GetPos().y, 1, 0, targetingCircle, true);
	}
	else DrawStringEx(200, 200, -1, "�I�[�g�^�[�Q�b�gOFF");


}

void Player::Init()
{
	pos = gManager->Center;
	gh = gManager->LoadGraphEx("graphics/Player_2525.png");

	targetingCircle = gManager->LoadGraphEx("graphics/TargetPointa.png");

	//player�̓����蔻�蔼�a
	radius = 12.5;

	//�ő剻�d�ʂ̃f�t�H���g
	maxCapacity = 500;

	//�X�e�[�W�����ړ�����X�s�[�h
	CruizeSpeed = 10;
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
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::DOWN)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::DOWN)];
	}

	//���E�L�[���m
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::RIGHT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::RIGHT)];
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::LEFT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::LEFT)];
	}

	//�ړ��ʂ�0�łȂ���΃x�N�g���𐳋K�����Ĉړ�������
	if (moveX != 0 || moveY != 0) {

		tnl::Vector3 fixVec = gManager->GetFixVector(moveX, moveY);

		float fixMoveX = fixVec.x * SPEED;
		float fixMoveY = fixVec.y * SPEED;

		pos.x += fixMoveX;
		pos.y += fixMoveY;

		//������ʒ[�ɂ���Ȃ�ړ����Ȃ�
		if (pos.x < radius || pos.x>1024 - radius ||
			pos.y < radius || pos.y>768 - radius) {
			pos.x -= fixMoveX;
			pos.y -= fixMoveY;
		}

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

	auto initPos = tnl::Vector3(0, -INITPOSY, 0);

	auto shootPoint = pos + initPos;


	//�e�̐���
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vec, Factory::MOVETYPE::STRAIGHT));
	bullet->SetList();
	bullet->SetBulletList();

}
void Player::SetMyTarget(std::shared_ptr<Object> Target)
{
	myTarget = Target;
}

//Player�ɐݒ肳�ꂽ�^�[�Q�b�g�Ɍ������Č��I�[�g�^�[�Q�b�g�ˌ��֐�
void Player::AimShootBullet()
{
	//MyTarget���ݒ肳��Ă��邩�m�F
	if (!isSetTarget()) {
		tnl::DebugTrace("\nMyTarget���ݒ肳��Ă��܂���\n");
		return;
	}

	//�N�[���_�E�����Ȃ甭�˂��Ȃ�
	if (shootTimer < SHOOTCOOLDOWN)return;
	//�N�[���_�E���Z�b�g
	shootTimer = 0;

	auto initPos = tnl::Vector3(0, -INITPOSY, 0);

	auto shootPoint = pos + initPos;

	//TargetPos�����̕����x�N�g�����擾���� ���K�����Ă��Ȃ����Ƃɒ���
	tnl::Vector3 pVec = myTarget->GetPos() - pos;


	////Target�̕����x�N�g����������������
	//tnl::Vector3 enemyVecSpeed = myTarget->GetVecSpeed() * gManager->deltatime;
	////�t�����Ȃ̂Ń}�C�i�X���|����
	//pVec += (enemyVecSpeed * -1);


	//�e�̐���
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, pVec, Factory::MOVETYPE::TOENEMY));
	bullet->SetList();
	bullet->SetBulletList();

}
//���ږړI�̃I�u�W�F�N�g�������ɂ���ČĂяo���I�[�g�^�[�Q�b�g�ˌ��֐�
void Player::AimShootBullet(std::shared_ptr<Object> Target)
{
	//�N�[���_�E�����Ȃ甭�˂��Ȃ�
	if (shootTimer < SHOOTCOOLDOWN)return;
	//�N�[���_�E���Z�b�g
	shootTimer = 0;

	tnl::DebugTrace("\n%d,%d,%d\n", pos.x, pos.y, pos.z);

	auto initPos = tnl::Vector3(0, -INITPOSY, 0);

	auto shootPoint = pos + initPos;

	//TargetPos�����̕����x�N�g�����擾���� ���K�����Ă��Ȃ����Ƃɒ���
	tnl::Vector3 pVec = Target->GetPos() - pos;

	//�e�̐���
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, pVec, Factory::MOVETYPE::TOENEMY));
	bullet->SetList();
	bullet->SetBulletList();
}

void Player::ShootMissile()
{
	//MyTarget���ݒ肳��Ă��邩�m�F
	if (!isSetTarget()) {
		tnl::DebugTrace("\nMyTarget���ݒ肳��Ă��܂���\n");
		return;
	}
	//�N�[���_�E�����Ȃ甭�˂��Ȃ�
	if (missileTimer < MISSILECOOLDOWN)return;
	//�N�[���_�E���Z�b�g
	missileTimer = 0;

	auto initPos = tnl::Vector3(0, -INITPOSY, 0);

	auto shootPoint = pos + initPos;

	tnl::Vector3 vPos = tnl::Vector3(0,-8.0f,0);

	//�e�̐���
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vPos, Factory::MOVETYPE::TRACKING));
	bullet->SetList();
	bullet->SetBulletList();
}
