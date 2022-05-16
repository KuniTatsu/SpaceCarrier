//Object‚ğ¶¬‚µ‚Ä•Ô‚·
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


	//Object‚ğŒp³‚µ‚½•¨‚ğì‚é‚Æ‚«‚Í‚±‚ÌŠÖ”‚ğŒÄ‚Ô
	std::shared_ptr<Object>create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move);
	std::shared_ptr<Object>create(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos);
private:
	//Œp³æ‚ÅÀ‘•‚·‚é
	virtual std::shared_ptr<Object>CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos) = 0;
	virtual std::shared_ptr<Object>CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move) = 0;

};
class ObjectFactory :public Factory {
public:
	ObjectFactory();
	//type‚É‚æ‚Á‚Ä¶¬‚·‚éObject‚ğ•ÏX‚·‚é
	std::shared_ptr<Object> CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move);

	std::shared_ptr<Object> CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos);
};

