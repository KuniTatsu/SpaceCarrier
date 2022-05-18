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
bool StraightShoot::Shoot(tnl::Vector3 Pos, int Radius, float Deltatime)
{
	//�N�[���_�E���^�C���̍X�V
	coolDown += Deltatime;
	//�N�[���_�E�������O�Ȃ猂�ĂȂ�
	if (coolDown < COOLTIME)return false;

	coolDown = 0;
	auto initPos = tnl::Vector3(0, +Radius, 0);

	auto shootPoint = Pos + initPos;


	//�e�̐���
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vecSpeed, Factory::MOVETYPE::STRAIGHT));
	bullet->SetList();
	//bullet->SetBulletList();
	bullet->SetEnemyBulletList();

	return true;
}
