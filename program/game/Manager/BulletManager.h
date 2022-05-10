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

	//void RemoveBullet(Bullet* bullet);

	inline std::list<std::shared_ptr<Bullet>>& GetList() {
		return liveBullet;
	}

	void RemoveBulletList();

private:
	//シングルトンインスタンス
	static BulletManager* instance;

	std::list<std::shared_ptr<Bullet>>liveBullet;

};

