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

	//’†SÀ•W‚Ìæ“¾
	inline tnl::Vector3& GetCenterPos() {
		return centerPos;
	}
	//UI‚Ì•‚Ìæ“¾
	inline int GetUIWidth() {
		return width;
	}

	//UI‚Ì‚‚³‚Ìæ“¾
	inline int GetUIHeight() {
		return height;
	}
	//UI‚Ì’¼‰ºYÀ•Wæ“¾
	inline int GetUnderBottomPos() {
		return static_cast<int>(underBottomPosY);
	}

private:

	GameManager* gManager = nullptr;

	//UIˆê‚Â‚Ì¶ã•`‰æÀ•W
	tnl::Vector3 pos = {};

	//UI‰æ‘œ‚Ì’†S•`‰æÀ•W
	tnl::Vector3 centerPos = {};

	//UI‚Ì˜g‚Ì‰¡•
	int width = 0;
	//UI‚Ì˜g‚Ìc•
	int height = 0;

	//˜g’¼‰º‚ÌyÀ•W
	float underBottomPosY = 0;

	//˜g‰æ‘œƒnƒ“ƒhƒ‹
	std::vector<int>frameGh;

	//˜g“à‚É•`‰æ‚·‚éUI‰æ‘œƒnƒ“ƒhƒ‹
	int drawUIGh = 0;

	void DrawFrame();
};

