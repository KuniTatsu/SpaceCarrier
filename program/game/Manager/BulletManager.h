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

	inline std::list<std::shared_ptr<Bullet>>& GetList() {
		return liveBullet;
	}

	//Bulletリストへの追加
	inline void AddBulletList(std::shared_ptr<Bullet> Ptr) {
		tnl::DebugTrace("\nBulletListに登録されました\n");
		liveBullet.emplace_back(Ptr);
	}
	void RemoveBulletList();

private:
	//シングルトンインスタンス
	static BulletManager* instance;

	std::list<std::shared_ptr<Bullet>>liveBullet;

};

