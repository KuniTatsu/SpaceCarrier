//enemyの状態が変化したら呼ばれるオブザーバクラス
//enemyの出現時にplayerのSetTarget関数を呼ぶ
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

	//player取得
	inline void SetPlayer(std::shared_ptr<Player>Player) {
		player = Player;
	}

	void DebugPlayer();
};

