#include "Factory.h"
#include"Object/Object.h"
#include"Object/Bullet.h"
#include"Object/Enemy.h"
#include"Object/Player.h"
#include"EnemyData.h"
#include"StrategyPattern/MovementPattern.h"
#include"StrategyPattern/ShootPattern.h"
#include"Manager/GameManager.h"
#include"Manager/EnemyManager.h"


ObjectFactory::ObjectFactory()
{
	//tnl::DebugTrace("\nFactory�q�N���X����������܂����B\n");
}

//�e�����֐�
std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	if (type == "Bullet") {
		//�ړ����@�ɂ���Đ�����ς���
		if (Move == MOVETYPE::STRAIGHT) {
			MovementBase* move = new StraightMove(VPos);
			return std::make_shared<Bullet>(StartPos, move);
		}
		//���_:�e���v���C���[�̂������W�Ɍ������Ĕ��ł����̂͂������A���̏ꏊ�ł����ƂƂǂ܂葱����n���ɂȂ��Ă��܂�
		//CenterStopMove�ł͂Ȃ��A�v���C���[��StartPos�̕����x�N�g�������A���K��,VPos�̑傫����������Straight�Ŕ�΂��ق����ǂ�����
		else if (Move == MOVETYPE::STOPPOS) {
			float speed = VPos.y;
			//MovementBase* move = new CenterStopMove(speed,)
			std::shared_ptr<Player>player = gManager->GetPlayer();
			tnl::Vector3 vec = player->GetPos() - StartPos;
			tnl::Vector3 fixVec = gManager->GetFixVector(vec.x, vec.y);

			MovementBase* move = new StraightMove(fixVec * speed);
			return std::make_shared<Bullet>(StartPos, move);
		}
		else if (Move == MOVETYPE::ACCEL) {

			MovementBase* move = new AccelMove(VPos);
			return std::make_shared<Bullet>(StartPos, move);
		}
		else if (Move == MOVETYPE::TOENEMY) {
			//VPos�𐳋K������
			tnl::Vector3 fixVec = gManager->GetFixVector(VPos.x, VPos.y);
			//���x ������ǂ������玝���Ă���
			float speed = 5.0f;
			//move�𐶐�
			MovementBase* move = new StraightMove(fixVec * speed);
			return std::make_shared<Bullet>(StartPos, move);
		}
		else if (Move == MOVETYPE::TRACKING) {
			std::shared_ptr<Player>player = gManager->GetPlayer();
			//player�̎����Ă���^�[�Q�b�g�̏����擾
			auto target = player->GetMyTarget();
			//�������𐶐�
			MovementBase* track = new ToTargetMove(VPos, target);

			return std::make_shared<Bullet>(StartPos, track);
		}
		return std::shared_ptr<Object>();
	}
}
//�G�����֐�
std::shared_ptr<Object>ObjectFactory::CreateObject(const tnl::Vector3& StartPos, const tnl::Vector3& VPos, std::shared_ptr<EnemyData>Data) {

	//�G�̃X�e�[�^�X�擾
	float* status = Data->GetStatus();
	//�G�摜�̃p�X�擾
	std::string pass = Data->GetGhPass();
	//������
	MovementBase* move = nullptr;
	//������
	ShootBase* shoot = nullptr;
	//����Ȍ�����
	ShootBase* exShoot = nullptr;

	//-------------------�ړ����@����-------------------//
	//�ړ����@�ɂ���Đ�����ς���
	if (Data->GetMoveType() == MOVETYPE::STRAIGHT) {
		move = new StraightMove(VPos);
	}
	else if (Data->GetMoveType() == MOVETYPE::FARSTOP) {
		move = new FarStopMove(VPos, 100);
	}
	else if (Data->GetMoveType() == MOVETYPE::MIDDLESTOP) {
		move = new FarStopMove(VPos, gManager->Center.y);
	}
	else if (Data->GetMoveType() == MOVETYPE::STOPPOS) {
		move = new CenterStopMove(2.0f, gManager->Center);
	}
	else if (Data->GetMoveType() == MOVETYPE::SLIDE) {
		
		move = new SlideMove(VPos);
	}
	else if (Data->GetMoveType() == MOVETYPE::ACCEL) {
		move = new AccelMove(VPos);
	}

	//-------------------�ˌ����@����-------------------//
	//�e�̔��˕��@�ɂ���Đ�����ς���
	//�����ˌ��Ȃ�
	if (Data->GetShootType() == SHOOTTYPE::STRAIGHT) {

		//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
		tnl::Vector3 vecSpeed = { 0,10,0 };
		float coolDawn = 0.5f;

		shoot = new StraightShoot(vecSpeed, coolDawn);
	}
	//�����ˌ��Ȃ�
	else if (Data->GetShootType() == SHOOTTYPE::FOCUS) {
		//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
		tnl::Vector3 vecSpeed = { 0,10,0 };
		float coolDawn = 0.5f;
		shoot = new FocusShoot(vecSpeed, coolDawn);
	}
	//�����ˌ��Ȃ�
	else if (Data->GetShootType() == SHOOTTYPE::FAST) {
		//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
		tnl::Vector3 vecSpeed = { 0,8,0 };
		float coolDawn = 0.25f;
		shoot = new FastShoot(vecSpeed, coolDawn);
	}

	//-------------------����ˌ����@����-------------------//
	//����ˌ���STRAIGHT�Ȃ�
	if (Data->GetExShootType() == SHOOTTYPE::STRAIGHT) {
		//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
		tnl::Vector3 vecSpeed = { 0,15,0 };
		float coolDawn = 0.5f;

		exShoot = new StraightShoot(vecSpeed, coolDawn);
	}
	//����ˌ���FOCUS�Ȃ�
	else if (Data->GetExShootType() == SHOOTTYPE::FOCUS) {
		//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
		tnl::Vector3 vecSpeed = { 0,10,0 };
		float coolDawn = 0.5f;

		exShoot = new FocusShoot(vecSpeed, coolDawn);
	}
	//����ˌ���FAST�Ȃ�
	else if (Data->GetExShootType() == SHOOTTYPE::FAST) {
		//�e�̑��x�x�N�g���ƃN�[���_�E���͂�����Csv����ǂݎ�肽��
		tnl::Vector3 vecSpeed = { 0,8,0 };
		float coolDawn = 0.25f;

		exShoot = new StraightShoot(vecSpeed, coolDawn);
	}


	//-------------enemy�����------------------
	//��������ˌ������Ȃ�
	if (exShoot != nullptr) {
		return std::make_shared<Enemy>(StartPos, pass, status[0], status[1], status[2], status[3], move, shoot, exShoot);
	}
	else
	{
		return std::make_shared<Enemy>(StartPos, pass, status[0], status[1], status[2], status[3], move, shoot);
	}

}

//memo ���[�U�[��鎞�Ɏg��->tnl::IsIntersectRayOBB


Factory::Factory()
{
	//tnl::DebugTrace("\nFactory�e�N���X����������܂����B\n");
	gManager = GameManager::Instance();
}

//--------------------------Object�^�𐶐�����֐�------------------------------------//

std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	auto object = CreateObject(type, StartPos, VPos, Move);

	return object;
}
//�G�����create�֐�
std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, ENEMYTYPE EnemyType)
{
	auto data = GetEnemyData(static_cast<int>(EnemyType));

	auto object = CreateObject(StartPos, VPos, data);

	return object;
}

void Factory::GetEnemyManager()
{
	eManager = EnemyManager::Instance();
}


std::shared_ptr<EnemyData> Factory::GetEnemyData(int EnemyType)
{
	return eManager->GetRandomEnemyData(EnemyType);
}



//------------------------------------------------------------------------------------//

