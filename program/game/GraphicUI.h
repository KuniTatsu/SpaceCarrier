#pragma once
#include"../dxlib_ext/dxlib_ext.h"
#include<string>
#include<vector>

class GameManager;

class GraphicUI
{
public:
	GraphicUI(tnl::Vector3 Pos, int FrameWidth, int FrameHeight, std::string FrameGh, std::string UIGh);
	~GraphicUI();

	void Draw();

	//中心座標の取得
	inline tnl::Vector3& GetCenterPos() {
		return centerPos;
	}
	//UIの幅の取得
	inline int GetUIWidth() {
		return width;
	}

	//UIの高さの取得
	inline int GetUIHeight() {
		return height;
	}
	//UIの直下Y座標取得
	inline int GetUnderBottomPos() {
		return static_cast<int>(underBottomPosY);
	}

private:

	GameManager* gManager = nullptr;

	//UI一つの左上描画座標
	tnl::Vector3 pos = {};

	//UI画像の中心描画座標
	tnl::Vector3 centerPos = {};

	//UIの枠の横幅
	int width = 0;
	//UIの枠の縦幅
	int height = 0;

	//枠直下のy座標
	float underBottomPosY = 0;

	//枠画像ハンドル
	std::vector<int>frameGh;

	//枠内に描画するUI画像ハンドル
	int drawUIGh = 0;

	void DrawFrame();
};

