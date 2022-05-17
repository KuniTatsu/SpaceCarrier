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
	//Player�̒e���X�g�̎擾
	inline std::list<std::shared_ptr<Bullet>>& GetList() {
		return liveBullet;
	}

	//player��Bullet���X�g�ւ̒ǉ�
	inline void AddBulletList(std::shared_ptr<Bullet> Ptr) {
		tnl::DebugTrace("\nBulletList�ɓo�^����܂���\n");
		liveBullet.emplace_back(Ptr);
	}
	//enemy��Bullet���X�g�ւ̒ǉ�
	inline void AddEnemyBulletList(std::shared_ptr<Bullet>Ptr) {
		tnl::DebugTrace("\n�G���e�𔭎˂��܂���\n");
		enemyBullet.emplace_back(Ptr);
	}

	void RemoveBulletList();

private:
	//�V���O���g���C���X�^���X
	static BulletManager* instance;
	//�v���C���[�̌������e�̃��X�g
	std::list<std::shared_ptr<Bullet>>liveBullet;

	//enemy�̌������e�̃��X�g
	std::list<std::shared_ptr<Bullet>>enemyBullet;

};

