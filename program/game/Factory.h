//Object�𐶐����ĕԂ�
#pragma once
#include<string>
#include"../dxlib_ext/dxlib_ext.h"
#include<memory>

class Object;
class Enemy;
class EnemyData;
class Bullet;
class MovementBase;
class GameManager;
class EnemyManager;

class Factory {
public:
	Factory();
	enum class MOVETYPE {
		STRAIGHT,
		STOPPOS,
		FARSTOP,
		MIDDLESTOP,
		ACCEL,
		SLIDE,
		TOENEMY,
		MAX
	};

	enum class SHOOTTYPE {
		STRAIGHT,
		FOCUS,
		FAST,
		DUMMY,
		NONE,
		MAX
	};

	enum class ENEMYTYPE :uint32_t {
		NORMAL,
		SEMIBOSS,
		BOSS,
		MAX
	};
	//enemyManager�擾
	void GetEnemyManager();


	//Object���p�������������Ƃ��͂��̊֐����Ă�
	std::shared_ptr<Object>create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move);
	//EnemyType�������Ă��čs�����̑���ǂݎ��֐�
	std::shared_ptr<Object> create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, ENEMYTYPE EnemyType);

	//enemy�𐶐����鎞�Ɏg�p����shootType�t���֐�
	std::shared_ptr<Object>create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot);

	std::shared_ptr<EnemyData> GetEnemyData(int EnemyType);

protected:
	GameManager* gManager = nullptr;
	EnemyManager* eManager = nullptr;
private:

	//�p����Ŏ�������
	virtual std::shared_ptr<Object>CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move) = 0;

	virtual std::shared_ptr<Object>CreateObject(const tnl::Vector3& StartPos, const tnl::Vector3& VPos, std::shared_ptr<EnemyData>Data) = 0;

};
class ObjectFactory :public Factory {
public:
	ObjectFactory();
	//type�ɂ���Đ�������Object��ύX����
	std::shared_ptr<Object>CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move);

	std::shared_ptr<Object>CreateObject(const tnl::Vector3& StartPos, const tnl::Vector3& VPos, std::shared_ptr<EnemyData>Data);
};

