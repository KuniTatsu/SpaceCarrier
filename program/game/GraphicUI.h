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

	//���S���W�̎擾
	inline tnl::Vector3& GetCenterPos() {
		return centerPos;
	}
	//UI�̕��̎擾
	inline int GetUIWidth() {
		return width;
	}

	//UI�̍����̎擾
	inline int GetUIHeight() {
		return height;
	}
	//UI�̒���Y���W�擾
	inline int GetUnderBottomPos() {
		return static_cast<int>(underBottomPosY);
	}

private:

	GameManager* gManager = nullptr;

	//UI��̍���`����W
	tnl::Vector3 pos = {};

	//UI�摜�̒��S�`����W
	tnl::Vector3 centerPos = {};

	//UI�̘g�̉���
	int width = 0;
	//UI�̘g�̏c��
	int height = 0;

	//�g������y���W
	float underBottomPosY = 0;

	//�g�摜�n���h��
	std::vector<int>frameGh;

	//�g���ɕ`�悷��UI�摜�n���h��
	int drawUIGh = 0;

	void DrawFrame();
};

