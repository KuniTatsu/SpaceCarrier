//Ingame内でドロップし、playerまで移動したら消去される
//ドロップアイテムのクラス

#pragma once
#include"Object.h"
#include<memory>

class MovementBase;
class Player;

class DropItem :Object
{
public:
	DropItem() {};
	DropItem(float startPosX, float startPosY);
	~DropItem();

	void Update()override;

	void Draw()override;

	void Init()override;
	//生死確認関数
	void CheckIsLive()override;

	inline float& GetRadius() {
		return radius;
	}

	inline bool GetIsLive() {
		return isLive;
	}

private:
	//動き方 playerを追尾する
	std::shared_ptr<MovementBase>myMove = nullptr;

	//playerインスタンス
	std::shared_ptr<Player>player = nullptr;
};

