#include "Factory.h"
#include"Object/Object.h"
#include"Object/Bullet.h"
#include"Object/Enemy.h"

ObjectFactory::ObjectFactory()
{
	tnl::DebugTrace("\nFactory�q�N���X����������܂����B\n");
}
std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	if (type == "Enemy") {
		return std::make_shared<Enemy>(StartPos);
	}
	else if (type == "Bullet") {
		return std::make_shared<Bullet>(StartPos, VPos);
	}
}
Factory::Factory()
{
	tnl::DebugTrace("\nFactory�e�N���X����������܂����B\n");
}

//Object�𐶐�����֐� type�ɂ���Đ��������p���悪�قȂ�
std::shared_ptr<Object> Factory::create(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	auto p = CreateObject(type, StartPos, VPos);
	//std::shared_ptr<Object> p = CreateObject(type, StartPos, VPos);
	return p;
}



