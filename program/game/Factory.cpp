#include "Factory.h"
#include"Object/Object.h"
#include"Object/Bullet.h"
#include"Object/Enemy.h"
#include"Movement/Movement.h"

ObjectFactory::ObjectFactory()
{
	tnl::DebugTrace("\nFactory子クラスが生成されました。\n");
}


std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	if (type == "Enemy") {
		//移動方法によって生成を変える
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
	tnl::DebugTrace("\nFactory親クラスが生成されました。\n");
}

//--------------------------Object型を生成する関数------------------------------------//
std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	auto p = CreateObject(type, StartPos, VPos, Move);
	
	//std::shared_ptr<Object> p = CreateObject(type, StartPos, VPos);
	return p;
}

//Objectを生成する関数 typeによって生成される継承先が異なる
std::shared_ptr<Object> Factory::create(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	auto p = CreateObject(type, StartPos, VPos);
	//std::shared_ptr<Object> p = CreateObject(type, StartPos, VPos);
	return p;
}

//------------------------------------------------------------------------------------//

