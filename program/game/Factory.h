//Object�𐶐����ĕԂ�
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

	//Object���p�������������Ƃ��͂��̊֐����Ă�
	std::shared_ptr<Object>create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move);
	//enemy�𐶐����鎞�Ɏg�p����shootType�t���֐�
	std::shared_ptr<Object>create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot);

private:
	//�p����Ŏ�������
	//virtual std::shared_ptr<Object>CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos) = 0;
	virtual std::shared_ptr<Object>CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot) = 0;
};
class ObjectFactory :public Factory {
public:
	ObjectFactory();
	//type�ɂ���Đ�������Object��ύX����
	std::shared_ptr<Object> CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot);


	//std::shared_ptr<Object> CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos);
};

