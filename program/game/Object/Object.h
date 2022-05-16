#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;

class Object:public std::enable_shared_from_this<Object>
{
protected:
	//描画座標
	tnl::Vector3 pos;
	//画像ハンドル
	int gh = 0;

	//当たり判定用の半径(円と円の衝突として実装する)
	int radius = 0;

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
	//半径の取得
	inline int& GetRadius() {
		return radius;
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

