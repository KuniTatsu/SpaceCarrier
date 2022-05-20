#include "Factory.h"
#include"Object/Object.h"
#include"Object/Bullet.h"
#include"Object/Enemy.h"
#include"EnemyData.h"
#include"StrategyPattern/MovementPattern.h"
#include"StrategyPattern/ShootPattern.h"
#include"Manager/GameManager.h"
#include"Manager/EnemyManager.h"

ObjectFactory::ObjectFactory()
{
	tnl::DebugTrace("\nFactory�q�N���X����������܂����B\n");
}

std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot)
{
	if (type == "Enemy") {
		//�ړ����@�ɂ���Đ�����ς���
		if (Move == MOVETYPE::STRAIGHT) {
			MovementBase* move = new StraightMove(VPos);

			//�e�̔��˕��@�ɂ���Đ�����ς���
			if (Shoot == SHOOTTYPE::STRAIGHT) {

				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* shoot = new StraightShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot);
			}
		}
		/*
		else if (Move == MOVETYPE::STOPPOS) {
			MovementBase* move = new CenterStopMove(2.0f, gManager->Center);
			//�e�̔��˕��@�ɂ���Đ�����ς���
			if (Shoot == SHOOTTYPE::STRAIGHT) {

				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* shoot = new StraightShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot);
			}
		}
		*/
	}
	else if (type == "Bullet") {
		//�ړ����@�ɂ���Đ�����ς���
		if (Move == MOVETYPE::STRAIGHT) {
			MovementBase* move = new StraightMove(VPos);
			return std::make_shared<Bullet>(StartPos, move);
		}
	}

}

std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos, MOVETYPE Move)
{
	if (type == "Bullet") {
		//�ړ����@�ɂ���Đ�����ς���
		if (Move == MOVETYPE::STRAIGHT) {
			MovementBase* move = new StraightMove(VPos);
			return std::make_shared<Bullet>(StartPos, move);
		}
		//���_:�e���v���C���[�̂������W�Ɍ������Ĕ��ł����̂͂������A���̏ꏊ�ł����ƂƂǂ܂葱����n���ɂȂ��Ă��܂�
		/*else if (Move == MOVETYPE::STOPPOS) {
			float speed = VPos.y;
			MovementBase* move = new CenterStopMove(speed,)
		}*/
		return std::shared_ptr<Object>();
	}
}

std::shared_ptr<Object>ObjectFactory::CreateObject(const tnl::Vector3& StartPos, const tnl::Vector3& VPos, std::shared_ptr<EnemyData>Data) {

	//�ړ����@�ɂ���Đ�����ς���
	if (Data->GetMoveType() == MOVETYPE::STRAIGHT) {
		MovementBase* move = new StraightMove(VPos);

		//�e�̔��˕��@�ɂ���Đ�����ς���
		if (Data->GetShootType() == SHOOTTYPE::STRAIGHT) {

			//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
			tnl::Vector3 vecSpeed = { 0,10,0 };
			float coolDawn = 0.5f;

			ShootBase* shoot = new StraightShoot(vecSpeed, coolDawn);
			//����ˌ��������Ȃ��G�Ȃ炻�̂܂ܐ���
			if (Data->GetExShootType() == SHOOTTYPE::NONE) {
				return std::make_shared<Enemy>(StartPos, move, shoot);
			}
			else if (Data->GetExShootType() == SHOOTTYPE::STRAIGHT) {
				//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* exShoot = new StraightShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot,exShoot);
			}
			else if (Data->GetExShootType() == SHOOTTYPE::FOCUS) {
				//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* exShoot = new FocusShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot, exShoot);
			}
			else if (Data->GetExShootType() == SHOOTTYPE::FAST) {
				//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* exShoot = new StraightShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot, exShoot);
			}
		}
	}
	//else if (Move == MOVETYPE::STOPPOS) {
	//	MovementBase* move = new CenterStopMove(2.0f, gManager->Center);
	//	//�e�̔��˕��@�ɂ���Đ�����ς���
	//	if (Shoot == SHOOTTYPE::STRAIGHT) {

	//		tnl::Vector3 vecSpeed = { 0,10,0 };
	//		float coolDawn = 0.5f;

	//		ShootBase* shoot = new StraightShoot(vecSpeed, coolDawn);
	//		return std::make_shared<Enemy>(StartPos, move, shoot);
	//	}
	//}

}

//memo ���[�U�[��鎞�Ɏg��->tnl::IsIntersectRayOBB

/*
std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	if (type == "Enemy") {
		return std::make_shared<Enemy>(StartPos);
	}
	else if (type == "Bullet") {
		return std::make_shared<Bullet>(StartPos, VPos);
	}
	return nullptr;
}
*/

Factory::Factory()
{
	tnl::DebugTrace("\nFactory�e�N���X����������܂����B\n");
	gManager = GameManager::Instance();
	eManager = EnemyManager::Instance();
}

//--------------------------Object�^�𐶐�����֐�------------------------------------//
std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	auto object = CreateObject(type, StartPos, VPos, Move, SHOOTTYPE::DUMMY);

	return object;
}
std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, ENEMYTYPE EnemyType)
{
	auto data = GetEnemyData(static_cast<int>(EnemyType));

	auto object = CreateObject(type, StartPos, VPos, , SHOOTTYPE::DUMMY);

	return object;
}

std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot)
{
	auto object = CreateObject(type, StartPos, VPos, Move, Shoot);

	return object;
}

std::shared_ptr<EnemyData> Factory::GetEnemyData(int EnemyType)
{
	return eManager->GetRandomEnemyData(EnemyType);
}

/*
//Object�𐶐�����֐� type�ɂ���Đ��������p���悪�قȂ�
std::shared_ptr<Object> Factory::create(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	auto p = CreateObject(type, StartPos, VPos);
	//std::shared_ptr<Object> p = CreateObject(type, StartPos, VPos);
	return p;
}
*/

//------------------------------------------------------------------------------------//

