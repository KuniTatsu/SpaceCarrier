#include "Player.h"
#include"../Manager/GameManager.h"
#include"Bullet.h"
#include"../Factory.h"

Player::Player()
{
	Init();
	tnl::DebugTrace("\nPlayerが作成されました\n");

}

Player::~Player()
{
}

void Player::Update()
{
	//移動
	Move();

	//弾発射タイマー更新
	shootTimer += gManager->deltatime;
}

void Player::Draw()
{
	gManager->DrawRotaGraphNormal(pos.x, pos.y, gh, true);
}

void Player::Init()
{
	pos = gManager->Center;
	gh = gManager->LoadGraphEx("graphics/Player_2525.png");

	//playerの当たり判定半径
	radius = 12.5;

	//最大化重量のデフォルト
	maxCapacity = 500;

	//ステージ内を移動するスピード
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
	//移動量リセット
	moveX = 0;
	moveY = 0;

	//どうにかしてまとめたい　関数化したいがうまく思いつかない
	//上下キー感知
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::UP)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::UP)];
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::DOWN)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::DOWN)];
	}

	//左右キー感知
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::RIGHT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::RIGHT)];
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::LEFT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::LEFT)];
	}

	//移動量が0でなければベクトルを正規化して移動させる
	if (moveX != 0 || moveY != 0) {

		tnl::Vector3 fixVec = GetFixVector(moveX, moveY);

		float fixMoveX = fixVec.x * SPEED;
		float fixMoveY = fixVec.y * SPEED;

		pos.x += fixMoveX;
		pos.y += fixMoveY;

		//もし画面端にいるなら移動しない
		if (pos.x < radius || pos.x>1024 - radius ||
			pos.y < radius || pos.y>768 - radius) {
			pos.x -= fixMoveX;
			pos.y -= fixMoveY;
		}

	}
}

void Player::ShootBullet()
{
	//クールダウン中なら発射しない
	if (shootTimer < SHOOTCOOLDOWN)return;
	//クールダウンセット
	shootTimer = 0;

	//速度ベクトルセット
	 tnl::Vector3 vec = { 0,-10,0 };

	tnl::DebugTrace("\n%d,%d,%d\n", pos.x, pos.y, pos.z);

	auto initPos = tnl::Vector3(0, -INITPOSY, 0);

	 auto shootPoint = pos + initPos;

	
	//弾の生成
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vec, Factory::MOVETYPE::STRAIGHT));
	bullet->SetList();
	bullet->SetBulletList();

}
