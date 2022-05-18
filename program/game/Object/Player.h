#pragma once
#include"Object.h"
#include<memory>
#include<math.h>

class GameManager;
class Factory;

class Player final :public Object
{
public:
	Player();
	~Player();

	void Update()override;
	void Draw()override;
	void Init()override;
	void CheckIsLive()override;
	//弾発射関数
	void ShootBullet();
	//巡航速度取得関数
	inline const float GetCruizeSpeed() {
		return CruizeSpeed;
	}

	//荷重率(荷重量/最大化重量)を取得する関数
	inline const float GetCapaciryRate() {
		return (haveCapacity / maxCapacity);
	}
private:

	void Move();

	//矢印キーの配列
	const tnl::Input::eKeys arrowKeys[static_cast<int>(DIR::MAX)] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT,
																		tnl::Input::eKeys::KB_DOWN, tnl::Input::eKeys::KB_LEFT };

	//キー取得
	inline tnl::Input::eKeys GetKeys(int KeyNum) {
		return arrowKeys[KeyNum];
	}

	//---------------画面内移動関係---------------------//

	//一時保管用X移動量
	float moveX = 0.0f;
	//一時保管用Y移動量
	float moveY = 0.0f;
	//
	//float fixMoveAmount = 0.0f;

	//移動スピード
	const int SPEED = 5;

	//移動キーを押したときの移動量
	const int MOVEAMOUNT[static_cast<int>(DIR::MAX)] = { -SPEED,SPEED,SPEED,-SPEED };

	//単位ベクトル取得関数
	inline tnl::Vector3 GetFixVector(float X, float Y) {

		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);

	}

	//---------------------------------------------------//

	//弾発射間隔
	const float SHOOTCOOLDOWN = 0.1f;
	//弾発射タイマー
	float shootTimer = 0.0f;

	//弾発射ポイント補正
	const float INITPOSY = 25.0f;


	//航行スピード ステージ内をゴールへ向かうスピード
	float CruizeSpeed = 0;

	//---------------荷重関係---------------------------//
	//荷重最大量 荷重量がこれを超えると航行スピードにペナルティが付く
	float maxCapacity = 0;
	//荷重量 運ぶ荷物の総重量 
	float haveCapacity = 0;

	//--------------------------------------------------//
	//objファクトリーポインタ
	Factory* fac = nullptr;
};

