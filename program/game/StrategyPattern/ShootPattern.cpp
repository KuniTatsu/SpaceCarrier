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
	////�N�[���_�E���^�C���̍X�V
	//coolDown += Deltatime;
	//�N�[���_�E�������O�Ȃ猂�ĂȂ�
	if (coolDown < COOLTIME)return false;
	return true;
}

//-------------------------------------------------------//

//------------------�����ˌ�----------------------------//
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
	////�N�[���_�E���^�C���̍X�V
	//coolDown += Deltatime;
	////�N�[���_�E�������O�Ȃ猂�ĂȂ�
	//if (coolDown < COOLTIME)return false;

	if (!CheckCoolDawn(Deltatime))return nullptr;

	//�N�[���_�E��������
	coolDown = 0;

	auto initPos = tnl::Vector3(0, +Radius, 0);

	auto shootPoint = Pos + initPos;


	//�e�̐���
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vecSpeed, Factory::MOVETYPE::STRAIGHT));
	bullet->SetList();
	//bullet->SetBulletList();
	//bullet->SetEnemyBulletList();

	return bullet;
}
//------------------�����ˌ�----------------------------//
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
	////�N�[���_�E���^�C���̍X�V
	//coolDown += Deltatime;
	////�N�[���_�E�������O�Ȃ猂�ĂȂ�
	//if (coolDown < COOLTIME)return false;

	if (!CheckCoolDawn(Deltatime))return nullptr;

	//�N�[���_�E��������
	coolDown = 0;
	auto initPos = tnl::Vector3(0, +Radius, 0);

	auto shootPoint = Pos + initPos;


	//�e�̐���
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vecSpeed, Factory::MOVETYPE::STOPPOS));
	bullet->SetList();
	//bullet->SetBulletList();
	//bullet->SetEnemyBulletList();

	return bullet;
}
//------------------�����ˌ�----------------------------//
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

	//�N�[���_�E��������
	coolDown = 0;

	auto initPos = tnl::Vector3(0, +Radius, 0);

	auto shootPoint = Pos + initPos;

	//�e�̐���
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

	//�N�[���_�E��������
	coolDown = 0;

	auto initPos = tnl::Vector3(Radius, 0, 0);

	auto shootPoint = Pos + initPos;

	//tnl::Vector3 vPos = tnl::Vector3(8.0f, 0, 0);

	//�e�̐���
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vecSpeed, Factory::MOVETYPE::TRACKING));
	bullet->SetList();
	//bullet->SetBulletList();

	return bullet;
}
