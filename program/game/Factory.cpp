#include "Factory.h"
#include"Object/Object.h"
#include"Object/Bullet.h"
#include"Object/Enemy.h"

ObjectFactory::ObjectFactory()
{
	tnl::DebugTrace("\nFactory子クラスが生成されました。\n");
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
	tnl::DebugTrace("\nFactory親クラスが生成されました。\n");
}

//Objectを生成する関数 typeによって生成される継承先が異なる
std::shared_ptr<Object> Factory::create(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	auto p = CreateObject(type, StartPos, VPos);
	//std::shared_ptr<Object> p = CreateObject(type, StartPos, VPos);
	return p;
}



