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

	//Enemy�̐����p��
	enum class ENEMYTYPE :uint32_t {
		NORMAL,
		SEMIBOSS,
		BOSS,
		MAX
	};


	//�G�̐����֐�(factory����Đ������Aenemy�̃X�}�[�g�|�C���^��Ԃ�
	std::shared_ptr<Enemy>CreateEnemy(ENEMYTYPE Type,tnl::Vector3 StartPos,tnl::Vector3 VPos);

	//�G�������Ƀ����_���œG��I������֐�
	std::shared_ptr<EnemyData>GetRandomEnemyData(int EnemyType);

private:
	//�V���O���g���C���X�^���X
	static EnemyManager* instance;

	//GameManager�|�C���^
	GameManager* gManager = nullptr;

	//obj�t�@�N�g���[�|�C���^
	Factory* fac = nullptr;

	//�����Ă���G�̃��X�g
	std::list<std::shared_ptr<Enemy>>liveEnemy;

	void LoadEnemyMaster();
	//���[�h���̈ꎞ�ۊǗp
	std::vector<std::vector<std::string>>loadEnemy;
	//���[�h����EnemyMaster
	std::vector < std::vector<std::shared_ptr<EnemyData>>>enemyMaster;



};
