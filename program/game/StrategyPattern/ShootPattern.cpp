#include "ShootPattern.h"
#include"../Object/Bullet.h"
#include"../Factory.h"
#include"../Manager/GameManager.h"

//------------------BaseClass----------------------------//
ShootBase::ShootBase()
{
	gManager = GameManager::Instance();
	fac = gManager->GetFactory();
}

ShootBase::~ShootBase()
{
}

void ShootBase::CoolDawnUpdate(const float Deltatime)
{
	coolDown += Deltatime;
}

bool ShootBase::CheckCoolDawn(const float Deltatime)
{
	////クールダウンタイムの更新
	//coolDown += Deltatime;
	//クールダウン解消前なら撃てない
	if (coolDown < COOLTIME)return false;
	return true;
}

//-------------------------------------------------------//

//------------------直線射撃----------------------------//
StraightShoot::StraightShoot(tnl::Vector3 VecSpeed, float CoolDawn)
{
	vecSpeed = VecSpeed;
	COOLTIME = CoolDawn;
}

StraightShoot::~StraightShoot()
{

}

//-------------------------------------------------------//
std::shared_ptr<Bullet> StraightShoot::Shoot(tnl::Vector3 Pos, int Radius, float Deltatime)
{
	////クールダウンタイムの更新
	//coolDown += Deltatime;
	////クールダウン解消前なら撃てない
	//if (coolDown < COOLTIME)return false;

	if (!CheckCoolDawn(Deltatime))return nullptr;

	//クールダウン初期化
	coolDown = 0;

	auto initPos = tnl::Vector3(0, +Radius, 0);

	auto shootPoint = Pos + initPos;


	//弾の生成
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vecSpeed, Factory::MOVETYPE::STRAIGHT));
	bullet->SetList();
	//bullet->SetBulletList();
	//bullet->SetEnemyBulletList();

	return bullet;
}
//------------------精密射撃----------------------------//
FocusShoot::FocusShoot(tnl::Vector3 VecSpeed, float CoolDawn)
{
	vecSpeed = VecSpeed;
	COOLTIME = CoolDawn;
}

FocusShoot::~FocusShoot()
{
}

std::shared_ptr<Bullet> FocusShoot::Shoot(tnl::Vector3 Pos, int Radius, float Deltatime)
{
	////クールダウンタイムの更新
	//coolDown += Deltatime;
	////クールダウン解消前なら撃てない
	//if (coolDown < COOLTIME)return false;

	if (!CheckCoolDawn(Deltatime))return nullptr;

	//クールダウン初期化
	coolDown = 0;
	auto initPos = tnl::Vector3(0, +Radius, 0);

	auto shootPoint = Pos + initPos;


	//弾の生成
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vecSpeed, Factory::MOVETYPE::STOPPOS));
	bullet->SetList();
	//bullet->SetBulletList();
	//bullet->SetEnemyBulletList();

	return bullet;
}
//------------------高速射撃----------------------------//
FastShoot::FastShoot(tnl::Vector3 VecSpeed, float CoolDawn)
{
	vecSpeed = VecSpeed;
	COOLTIME = CoolDawn;
}

FastShoot::~FastShoot()
{
}

std::shared_ptr<Bullet> FastShoot::Shoot(tnl::Vector3 Pos, int Radius, float Deltatime)
{
	if (!CheckCoolDawn(Deltatime))return nullptr;

	//クールダウン初期化
	coolDown = 0;

	auto initPos = tnl::Vector3(0, +Radius, 0);

	auto shootPoint = Pos + initPos;

	//弾の生成
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vecSpeed, Factory::MOVETYPE::ACCEL));
	bullet->SetList();
	//bullet->SetEnemyBulletList();

	return bullet;
}

TrackShoot::TrackShoot(tnl::Vector3 VecSpeed, float CoolDawn)
{
	vecSpeed = VecSpeed;
	COOLTIME = CoolDawn;
}

TrackShoot::~TrackShoot()
{
}

std::shared_ptr<Bullet> TrackShoot::Shoot(tnl::Vector3 Pos, int Radius, float Deltatime)
{
	if (!CheckCoolDawn(Deltatime))return nullptr;

	//クールダウン初期化
	coolDown = 0;

	auto initPos = tnl::Vector3(Radius, 0, 0);

	auto shootPoint = Pos + initPos;

	//tnl::Vector3 vPos = tnl::Vector3(8.0f, 0, 0);

	//弾の生成
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vecSpeed, Factory::MOVETYPE::TRACKING));
	bullet->SetList();
	//bullet->SetBulletList();

	return bullet;
}
