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
	//�C���X�^���X���Ȃ���ΐ����A����ΕԂ��֐�
	static EnemyManager* Instance();

	//Bullet���X�g�̏�����
	inline void ResetEnemyList() {
		liveEnemy.clear();
	}

	inline std::list<std::shared_ptr<Enemy>>& GetList() {
		return liveEnemy;
	}

	//Bullet���X�g�ւ̒ǉ�
	inline void AddEnemyList(std::shared_ptr<Enemy> Ptr) {
		tnl::DebugTrace("\nEnemyList�ɓo�^����܂���\n");
		liveEnemy.emplace_back(Ptr);
	}
	void RemoveEnemyList();

private:
	//�V���O���g���C���X�^���X
	static EnemyManager* instance;

	std::list<std::shared_ptr<Enemy>>liveEnemy;
};
