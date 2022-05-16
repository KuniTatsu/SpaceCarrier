#include "Factory.h"
#include"Object/Object.h"
#include"Object/Bullet.h"
#include"Object/Enemy.h"
#include"Movement/Movement.h"

ObjectFactory::ObjectFactory()
{
	tnl::DebugTrace("\nFactory�q�N���X����������܂����B\n");
}


std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	if (type == "Enemy") {
		//�ړ����@�ɂ���Đ�����ς���
		if (Move == MOVETYPE::STRAIGHT) {
			MovementBase* move = new StraightMove(VPos);
			return std::make_shared<Enemy>(StartPos, move);
		}



	}

}


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


Factory::Factory()
{
	tnl::DebugTrace("\nFactory�e�N���X����������܂����B\n");
}

//--------------------------Object�^�𐶐�����֐�------------------------------------//
std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	auto p = CreateObject(type, StartPos, VPos, Move);
	
	//std::shared_ptr<Object> p = CreateObject(type, StartPos, VPos);
	return p;
}

//Object�𐶐�����֐� type�ɂ���Đ��������p���悪�قȂ�
std::shared_ptr<Object> Factory::create(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	auto p = CreateObject(type, StartPos, VPos);
	//std::shared_ptr<Object> p = CreateObject(type, StartPos, VPos);
	return p;
}

//------------------------------------------------------------------------------------//

