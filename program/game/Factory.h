//Objectを生成して返す
#pragma once
#include<string>
#include"../dxlib_ext/dxlib_ext.h"
#include<memory>

class Object;
class Enemy;
class Bullet;
class MovementBase;

class Factory {
public:
	Factory();
	enum class MOVETYPE {
		STRAIGHT,
		CURVE,
		MAX
	};

	enum class SHOOTTYPE {
		STRAIGHT,
		DUMMY,
		MAX
	};

	//Objectを継承した物を作るときはこの関数を呼ぶ
	std::shared_ptr<Object>create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move);
	//enemyを生成する時に使用するshootType付き関数
	std::shared_ptr<Object>create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot);

private:
	//継承先で実装する
	//virtual std::shared_ptr<Object>CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos) = 0;
	virtual std::shared_ptr<Object>CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot) = 0;
};
class ObjectFactory :public Factory {
public:
	ObjectFactory();
	//typeによって生成するObjectを変更する
	std::shared_ptr<Object> CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot);


	//std::shared_ptr<Object> CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos);
};

