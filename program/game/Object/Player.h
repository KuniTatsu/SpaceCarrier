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

	//特定の敵をターゲットする関数
	void SetMyTarget(std::shared_ptr<Object> Target);
	//ターゲットを初期化する関数
	inline void	CleanTarget() {
		myTarget = nullptr;
	}
	//オートターゲット自動更新を切り替える関数
	inline void	ChageAutoTargerMode() {
		if (autoTargetMode) {
			autoTargetMode = false;
			return;
		}
		autoTargetMode = true;
	}
	//オートターゲット自動更新の確認関数
	inline bool	isAutoTargetMode() {
		return autoTargetMode;
	}

	//特定の目標に向かって射撃する関数
	void AimShootBullet();
	void AimShootBullet(std::shared_ptr<Object>Target);

	//誘導ミサイル
	void ShootMissile();

	//MyTargetが設定されているか確認する関数 true:設定されている,false:設定されていない
	inline bool isSetTarget() {
		if (myTarget != nullptr)return true;
		return false;
	}

	inline std::shared_ptr<Object>GetMyTarget() {
		return myTarget;
	}

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

	//規定方向ベクトル
	const tnl::Vector3 FRONT = { 0,-1,0 };

	//---------------------------------------------------//

	//---------------射撃関係---------------------------//
	//弾発射間隔
	const float SHOOTCOOLDOWN = 0.1f;
	//弾発射タイマー
	float shootTimer = 0.0f;

	//Missileクールダウン
	const float MISSILECOOLDOWN = 1.0f;

	//Missile発射タイマー
	float missileTimer = 0.0f;

	//弾発射ポイント補正
	const float INITPOSY = 25.0f;

	//弾の速度
	const float BULLETSPEED = 5.0f;

	//オートターゲット用
	std::shared_ptr<Object> myTarget = nullptr;

	//オートターゲットモード
	bool autoTargetMode = false;

	//航行スピード ステージ内をゴールへ向かうスピード
	float CruizeSpeed = 0;

	//---------------荷重関係---------------------------//
	//荷重最大量 荷重量がこれを超えると航行スピードにペナルティが付く
	float maxCapacity = 0;
	//荷重量 運ぶ荷物の総重量 
	float haveCapacity = 0;

	//--------------------------------------------------//
	
	//-----------------画像関係---------------//
	//オートターゲット標準gh
	int targetingCircle = 0;

	//objファクトリーポインタ
	Factory* fac = nullptr;
};

