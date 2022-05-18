#pragma once
#include<list>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"

class Enemy;

class EnemyManager
{
protected:
	EnemyManager();
	~EnemyManager();

public:
	//インスタンスがなければ生成、あれば返す関数
	static EnemyManager* Instance();

	//Bulletリストの初期化
	inline void ResetEnemyList() {
		liveEnemy.clear();
	}

	inline std::list<std::shared_ptr<Enemy>>& GetList() {
		return liveEnemy;
	}

	//Bulletリストへの追加
	inline void AddEnemyList(std::shared_ptr<Enemy> Ptr) {
		tnl::DebugTrace("\nEnemyListに登録されました\n");
		liveEnemy.emplace_back(Ptr);
	}
	void RemoveEnemyList();

private:
	//シングルトンインスタンス
	static EnemyManager* instance;

	std::list<std::shared_ptr<Enemy>>liveEnemy;
};
