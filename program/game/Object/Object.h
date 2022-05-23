#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;

class Object :public std::enable_shared_from_this<Object>
{
protected:
	//描画座標
	tnl::Vector3 pos;
	//画像ハンドル
	int gh = 0;

	//速度ベクトル
	tnl::Vector3 vecSpeed = {};

	//当たり判定用の半径(円と円の衝突として実装する)
	float radius = 0;

	GameManager* gManager = nullptr;

	bool isLive = true;

	//方向
	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};
public:
	Object();

	void SetList();
	//生死状態の獲得
	inline bool& GetIsLive() {
		return isLive;
	}

	inline void	SetIsLive() {
		isLive = false;
	}

	//描画座標の取得
	inline tnl::Vector3& GetPos() {
		return pos;
	}
	//描画座標のセット
	inline void	SetPos(tnl::Vector3 Pos) {
		pos = Pos;
	}

	//半径の取得
	inline float& GetRadius() {
		return radius;
	}

	//速度ベクトル取得関数
	inline tnl::Vector3 GetVecSpeed() {
		return vecSpeed;
	}

	virtual~Object() {};

	//*******純粋仮想関数 継承先で実装************//
	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Init() = 0;
	//生死確認関数
	virtual	void CheckIsLive() = 0;

private:
};

