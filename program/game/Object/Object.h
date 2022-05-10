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

	GameManager* gManager = nullptr;

	bool isLive = true;
public:
	Object();

	void SetList();
	inline bool& GetIsLive() {
		return isLive;
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

