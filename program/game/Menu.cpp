#include "Menu.h"
#include"Manager/GameManager.h"

Menu::Menu(int MenuTopX, int MenuTopY, int Width, int Height, std::string GhPath)
{
	gManager = GameManager::Instance();


	menuTopPos = tnl::Vector3(MenuTopX, MenuTopY, 0);

	width = Width;
	height = Height;
	menuBackGroundGhPass = GhPath;

	gManager->LoadDivGraphEx(GhPath, 9, 3, 3, 16, 16, menuBackGroundGh);


}

void Menu::MenuDraw()
{
	//��i
	DrawGraph(menuTopPos.x, menuTopPos.y, menuBackGroundGh[0], true);
	DrawExtendGraph(menuTopPos.x + 16, menuTopPos.y, menuTopPos.x + width - 16, menuTopPos.y + 16, menuBackGroundGh[1], true);
	DrawGraph(menuTopPos.x + width - 16, menuTopPos.y, menuBackGroundGh[2], true);

	//���i
	DrawExtendGraph(menuTopPos.x, menuTopPos.y + 16, menuTopPos.x + 16, menuTopPos.y + height - 16, menuBackGroundGh[3], true);
	DrawExtendGraph(menuTopPos.x + 16, menuTopPos.y + 16, menuTopPos.x + width - 16, menuTopPos.y + height - 16, menuBackGroundGh[4], true);
	DrawExtendGraph(menuTopPos.x + width - 16, menuTopPos.y + 16, menuTopPos.x + width, menuTopPos.y + height - 16, menuBackGroundGh[5], true);

	//���i
	DrawGraph(menuTopPos.x, menuTopPos.y + height - 16, menuBackGroundGh[6], true);
	DrawExtendGraph(menuTopPos.x + 16, menuTopPos.y + height - 16, menuTopPos.x + width - 16, menuTopPos.y + height, menuBackGroundGh[7], true);
	DrawGraph(menuTopPos.x + width - 16, menuTopPos.y + height - 16, menuBackGroundGh[8], true);
}

SelectMenu::SelectMenu(int TopX, int TopY, int Width, int Height, std::string GhPath)
	: Menu(TopX, TopY, Width, Height, GhPath)//���j���[�̑傫�������߂�(�J�n���W:����,����,�c��)
{
	highLightGh = gManager->LoadGraphEx("graphics/MenuHighLight.png");


}

SelectMenu::~SelectMenu()
{
}

void SelectMenu::AddMenuElements(std::string Text)
{
	//�܂����j���[���ڂ��Ȃ����Menu�̘g���甼���������炵�Đ������遨���S���W�ɂ���
	if (elements.empty()) {
		auto element = std::make_unique<Element>(menuTopPos.x + (width / 2), menuTopPos.y + 10, Text);
		elements.emplace_back(std::move(element));
		return;
	}
	//���j���[����������Ă���΁A�����̍��ڂ�y���W����I�t�Z�b�g���������炵�Đ�������
	auto element = std::make_unique<Element>(menuTopPos.x + (width / 2), elements.back()->centerPos.y + 25, Text);
	elements.emplace_back(std::move(element));


}

bool SelectMenu::MenuUpdate()
{
	//���j���[�̑I�𒆍��ڂ̈ړ�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		nowSelectNum = (nowSelectNum + (elements.size() - 1)) % elements.size();
		//tnl::DebugTrace("\n[%d]�ԃ��j���[�I��\n", nowSelectNum);
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		nowSelectNum = (nowSelectNum + 1) % elements.size();
		//tnl::DebugTrace("\n[%d]�ԃ��j���[�I��\n", nowSelectNum);
	}


	return false;
}

bool SelectMenu::CheckMenuClick()
{
	for (int i = 0; i < elements.size(); ++i) {
		if (elements[i]->isClickElement()) {
			nowSelectNum = i;
			return true;
		}
	}

	return false;
}



void SelectMenu::DrawSelectMenu()
{
	//�w�i�̕`��
	MenuDraw();

	//���j���[���ڂ̕`��
	for (int i = 0; i < elements.size(); ++i) {
		elements[i]->DrawElement();
	}

	//--------------�I�𒆍��ڂ̃n�C���C�g---------------------//
	//�A���t�@�����ɕύX
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//�`��̈�̎w��
	//SetDrawArea(menuTopPos.x, menuTopPos.y, menuTopPos.x + width, menuTopPos.y + height);

	//�n�C���C�g�摜�̕`��
	DrawRotaGraph(elements[nowSelectNum]->centerPos.x, elements[nowSelectNum]->centerPos.y, 1, 0, highLightGh, false);

	//SetDrawArea(0, 0, 1024, 768);
	//�u�����h���[�h��߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}



//--------------Menu����,�w�i�摜,�����蔻��p�N���X--------------//
Element::Element(float CenterX, float CenterY, std::string Text)
{
	gManager = GameManager::Instance();

	centerPos.x = CenterX;
	centerPos.y = CenterY + 10;

	leftPos.x = CenterX - TEXTRECT.x / 2;
	leftPos.y = CenterY - TEXTRECT.y / 2;

	element = Text;

	gh = gManager->LoadGraphEx("graphics/MenuRect.png");
}

Element::~Element()
{
}

bool Element::isClickElement()
{
	if (gManager->isClickedRect(gManager->mousePosX, gManager->mousePosY, leftPos.x, leftPos.y, leftPos.x + TEXTRECT.x, leftPos.y + TEXTRECT.y))
	{
		return true;
	}
	return false;
}

void Element::DrawElement()
{
	DrawRotaGraph(centerPos.x, centerPos.y, 1, 0, gh, false);

	DrawStringEx(leftPos.x + 10, centerPos.y-10, -1, element.c_str());
}
