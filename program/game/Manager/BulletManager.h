#pragma once
#include "../Object/Bullet.h";
#include<list>
#include<memory>

class Bullet;

class BulletManager
{
protected:
	BulletManager();
	~BulletManager();

public:
	//インスタンスがなければ生成、あれば返す関数
	static BulletManager* Instance();

	//Bulletリストの初期化
	inline void ResetBulletList() {
		liveBullet.clear();
	}
	//Playerの弾リストの取得
	inline std::list<std::shared_ptr<Bullet>>& GetList() {
		return liveBullet;
	}

	//playerのBulletリストへの追加
	inline void AddBulletList(std::shared_ptr<Bullet> Ptr) {
		tnl::DebugTrace("\nBulletListに登録されました\n");
		liveBullet.emplace_back(Ptr);
	}
	//enemyのBulletリストへの追加
	inline void AddEnemyBulletList(std::shared_ptr<Bullet>Ptr) {
		tnl::DebugTrace("\n敵が弾を発射しました\n");
		enemyBullet.emplace_back(Ptr);
	}

	void RemoveBulletList();

private:
	//シングルトンインスタンス
	static BulletManager* instance;
	//プレイヤーの撃った弾のリスト
	std::list<std::shared_ptr<Bullet>>liveBullet;

	//enemyの撃った弾のリスト
	std::list<std::shared_ptr<Bullet>>enemyBullet;

};

