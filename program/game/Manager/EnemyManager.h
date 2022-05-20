#pragma once
#include<list>
#include<memory>
#include<vector>
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

class Enemy;
class EnemyData;
class Factory;
class GameManager;

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

	//Enemyの生成用列挙
	enum class ENEMYTYPE :uint32_t {
		NORMAL,
		SEMIBOSS,
		BOSS,
		MAX
	};


	//敵の生成関数(factoryを介して生成し、enemyのスマートポインタを返す
	std::shared_ptr<Enemy>CreateEnemy(ENEMYTYPE Type,tnl::Vector3 StartPos,tnl::Vector3 VPos);

	//敵生成時にランダムで敵を選択する関数
	std::shared_ptr<EnemyData>GetRandomEnemyData(int EnemyType);

private:
	//シングルトンインスタンス
	static EnemyManager* instance;

	//GameManagerポインタ
	GameManager* gManager = nullptr;

	//objファクトリーポインタ
	Factory* fac = nullptr;

	//生きている敵のリスト
	std::list<std::shared_ptr<Enemy>>liveEnemy;

	void LoadEnemyMaster();
	//ロード時の一時保管用
	std::vector<std::vector<std::string>>loadEnemy;
	//ロードしたEnemyMaster
	std::vector < std::vector<std::shared_ptr<EnemyData>>>enemyMaster;



};
