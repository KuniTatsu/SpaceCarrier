#include "GraphicUI.h"
#include"Manager/GameManager.h"

GraphicUI::GraphicUI(tnl::Vector3 Pos, int FrameWidth, int FrameHeight, std::string FrameGh, std::string UIGh)
{
	gManager = GameManager::Instance();

	pos = Pos;
	width = FrameWidth;
	height = FrameHeight;

	//���S���W���擾
	centerPos = tnl::Vector3(pos.x + (width >> 1), pos.y + (height >> 1), 0);

	underBottomPosY = centerPos.y + (height >> 1)+50;

	//�g�̉摜�̕������[�h
	gManager->LoadDivGraphEx(FrameGh, 9, 3, 3, 16, 16, frameGh);
	//�g���ɕ`�悷��UI�摜�̃��[�h
	drawUIGh = gManager->LoadGraphEx(UIGh);
}

GraphicUI::~GraphicUI()
{
}

void GraphicUI::Draw()
{
	DrawFrame();
	DrawRotaGraph(centerPos.x, centerPos.y, 0.98, 0, drawUIGh, true);
}

void GraphicUI::DrawFrame()
{
	//�g�̏�i�̕`��
	DrawGraph(pos.x, pos.y, frameGh[0], true);
	DrawExtendGraph(pos.x + 16, pos.y, pos.x + width - 16, pos.y + 16, frameGh[1], true);
	DrawGraph(pos.x + width - 16, pos.y, frameGh[2], true);

	//�g�̒��i�̕`��
	DrawExtendGraph(pos.x, pos.y + 16, pos.x + 16, pos.y + height - 16, frameGh[3], true);
	DrawExtendGraph(pos.x + 16, pos.y + 16, pos.x + width - 16, pos.y + height - 16, frameGh[4], true);
	DrawExtendGraph(pos.x + width - 16, pos.y + 16, pos.x + width, pos.y + height - 16, frameGh[5], true);

	//�g�̉��i�̕`��
	DrawGraph(pos.x, pos.y + height - 16, frameGh[6], true);
	DrawExtendGraph(pos.x + 16, pos.y + height - 16, pos.x + width - 16, pos.y + height, frameGh[7], true);
	DrawGraph(pos.x + width - 16, pos.y + height - 16, frameGh[8], true);
}
