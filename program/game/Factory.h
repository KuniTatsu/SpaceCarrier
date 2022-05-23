//Objectを生成して返す
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
	//enemyManager取得
	void GetEnemyManager();


	//Objectを継承した物を作るときはこの関数を呼ぶ
	std::shared_ptr<Object>create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move);
	//EnemyTypeを持ってきて行動その他を読み取る関数
	std::shared_ptr<Object> create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, ENEMYTYPE EnemyType);

	//enemyを生成する時に使用するshootType付き関数
	std::shared_ptr<Object>create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot);

	std::shared_ptr<EnemyData> GetEnemyData(int EnemyType);

protected:
	GameManager* gManager = nullptr;
	EnemyManager* eManager = nullptr;
private:

	//継承先で実装する
	virtual std::shared_ptr<Object>CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move) = 0;

	virtual std::shared_ptr<Object>CreateObject(const tnl::Vector3& StartPos, const tnl::Vector3& VPos, std::shared_ptr<EnemyData>Data) = 0;

};
class ObjectFactory :public Factory {
public:
	ObjectFactory();
	//typeによって生成するObjectを変更する
	std::shared_ptr<Object>CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move);

	std::shared_ptr<Object>CreateObject(const tnl::Vector3& StartPos, const tnl::Vector3& VPos, std::shared_ptr<EnemyData>Data);
};

