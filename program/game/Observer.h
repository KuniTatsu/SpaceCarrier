//enemy�̏�Ԃ��ω�������Ă΂��I�u�U�[�o�N���X
//enemy�̏o������player��SetTarget�֐����Ă�
#pragma once
#include<memory>

class Enemy;
class Player;
class GameManager;
class EnemyManager;

class Observer
{
private:
	friend class Enemy;
	GameManager* gManager = nullptr;
	std::shared_ptr<Player>player = nullptr;
	EnemyManager* eManager = nullptr;

public:
	Observer();
	~Observer();

	void Update(std::shared_ptr<Enemy>enemy);

	//player�擾
	inline void SetPlayer(std::shared_ptr<Player>Player) {
		player = Player;
	}

	void DebugPlayer();
};

