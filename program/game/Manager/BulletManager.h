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
	//�C���X�^���X���Ȃ���ΐ����A����ΕԂ��֐�
	static BulletManager* Instance();

	//Bullet���X�g�̏�����
	inline void ResetBulletList() {
		liveBullet.clear();
	}

	inline std::list<std::shared_ptr<Bullet>>& GetList() {
		return liveBullet;
	}

	//Bullet���X�g�ւ̒ǉ�
	inline void AddBulletList(std::shared_ptr<Bullet> Ptr) {
		tnl::DebugTrace("\nBulletList�ɓo�^����܂���\n");
		liveBullet.emplace_back(Ptr);
	}
	void RemoveBulletList();

private:
	//�V���O���g���C���X�^���X
	static BulletManager* instance;

	std::list<std::shared_ptr<Bullet>>liveBullet;

};

