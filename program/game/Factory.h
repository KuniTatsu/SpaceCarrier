//Object�𐶐����ĕԂ�
#pragma once
#include<string>
#include"../dxlib_ext/dxlib_ext.h"
#include<memory>

class Object;
class Enemy;
class Bullet;

class Factory {
public:
	Factory();
	//Object���p�������������Ƃ��͂��̊֐����Ă�
	std::shared_ptr<Object>create(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos);
private:
	//�p����Ŏ�������
	virtual std::shared_ptr<Object>CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos) = 0;

};
class ObjectFactory :public Factory {
public:
	ObjectFactory();
	//type�ɂ���Đ�������Object��ύX����
	std::shared_ptr<Object> CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos);
};

