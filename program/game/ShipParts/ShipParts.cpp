#include "ShipParts.h"
#include"../Manager/GameManager.h"
#include"../Manager/ModManager.h"
#include"../Mod.h"
#include"../Menu.h"

ShipParts::ShipParts(int Id, int PartsType, std::string Name, float Hp, float Energy, float Defence, float Speed, std::string GhPass,
	std::string IconPass, float ContainerAmount)
{
	gManager = GameManager::Instance();
	mManager = ModManager::Instance();

	//------------��{�f�[�^�̑��------------------//
	partsId = Id;
	partsType = PartsType;

	partsName = Name;

	hp = Hp;
	energy = Energy;
	defence = Defence;
	speed = Speed;
	containerAmount = ContainerAmount;

	basicStatus[0] = hp;
	basicStatus[1] = energy;
	basicStatus[2] = defence;
	basicStatus[3] = speed;
	basicStatus[4] = containerAmount;

	pass = GhPass;
	gh = gManager->LoadGraphEx(GhPass);

	iconPass = IconPass;
	iconGh = gManager->LoadGraphEx(IconPass);

	iconBachGh = gManager->LoadGraphEx("graphics/ShipParts/Icon_Back_fix.png");
	iconEquipGh = gManager->LoadGraphEx("graphics/ShipParts/Icon_Back_Equiped.png");

	highRight = gManager->LoadGraphEx("graphics/ShipParts/Icon_Back_test.png");

	statusBack = std::make_shared<Menu>(500, 320, 140, 120, "graphics/FrameBlack.png");

	modNameBack = std::make_shared<Menu>(400, 320, 90, 120, "graphics/FrameBlack.png");

	//�ȉ��̏����̓}�X�^�[�������ɂ͎��s���Ȃ�
	if (!gManager->GetLoadedFlag())return;

	//-------------�C��Mod�̌���(����Ȃ��܂�)------------------//
	//����0~2��
	//0:1:2=40:50:10%
	int modNum = 0;

	int rand = GetRand(100);
	if (rand >= 40 && rand < 90)modNum = 1;
	else if (rand >= 90)modNum = 2;

	//����mod�����Ȃ��p�[�c�Ȃ炱���Ŗ��O�����߂ď������I����
	if (modNum == 0) {
		factName = partsName;

		//���O�̒������擾����(���������ŕ`�悷�邽��)
		// ������̒������擾
		int StrLen = strlen(factName.c_str());

		// �`�掞�̕�����̕����擾
		strWidth = GetDrawStringWidth(factName.c_str(), StrLen);

		//���v�X�e�[�^�X�̎擾
		SetTrueStatus();
		return;
	}

	//modNum�̌���mod��t�^����
	for (int i = 0; i <= modNum; ++i) {
		auto mod = mManager->CreateNewMod();
		myMods.emplace_back(mod);
		tnl::DebugTrace("\n�C��Mod[%s]��t�^���܂���\n", mod->GetModName().c_str());
	}
	//Mod�X�e�[�^�X�̎擾
	SetEditStatus();
	//���v�X�e�[�^�X�̎擾
	SetTrueStatus();

	//�P�ڂ�Mod�̖��O���p�[�c�̖��O�ɉ����ĕ\������
	factName = myMods[0]->GetModName() + partsName;

	// ������̒������擾
	int StrLen = strlen(factName.c_str());

	// �`�掞�̕�����̕����擾
	strWidth = GetDrawStringWidth(factName.c_str(), StrLen);
}

ShipParts::~ShipParts()
{
}

void ShipParts::DrawParts(int X, int Y)
{
	DrawRotaGraph(X, Y, 1, 0, gh, true);
}

void ShipParts::DrawPartsIcon(int X, int Y)
{
	//-----------�n�C���C�g�\��--------------
	//�}�E�X���A�C�R���摜�̒��ɂ���΂��̃A�C�R���摜�̔w�i���n�C���C�g����
	if (gManager->mousePosX >= X - 90 && gManager->mousePosX <= X + 90 &&
		gManager->mousePosY >= Y - 112 && gManager->mousePosY <= Y + 112
		) {
		DrawRotaGraph(X, Y, 1.5, 0, highRight, false);
		if (!isCursored)isCursored = true;
	}
	else {
		if (isCursored)isCursored = false;
	}
	//-----------------------------

	//��������Ă�����w�i�摜��ς���
	if (isEquiped) DrawRotaGraph(X, Y, 1.5, 0, iconEquipGh, true);
	else DrawRotaGraph(X, Y, 1.5, 0, iconBachGh, true);

	DrawRotaGraph(X, Y, 1.5, 0, iconGh, false);

	iconCenter.x = X;
	iconCenter.y = Y;

	////�}�E�X���A�C�R���摜�̒��ɂ���΂��̑����̃X�e�[�^�X��\������
	//if (gManager->mousePosX >= X - 90 && gManager->mousePosX <= X + 90 &&
	//	gManager->mousePosY >= Y - 112 && gManager->mousePosY <= Y + 112)
	//{
	//	statusBack->MenuDraw();

	//	auto pos = statusBack->GetTopPos();
	//	DrawPartsStatus(pos.x + 10, pos.y + 10);
	//}


}
//�C��Mod�̎��X�e�[�^�X�̍��v
void ShipParts::SetEditStatus()
{
	//mod�������Ȃ��Ȃ�v�Z���Ȃ�
	if (myMods.empty()) {
		for (int i = 0; i < 5; ++i) {
			addStatus[i] = 0;
		}
		return;
	}

	//�S�Ă�Mod����X�e�[�^�X�����ꂼ����Z����
	for (auto mod : myMods) {

		auto status = mod->GetBasicStatus();

		addHp += status[0];
		addEnergy += status[1];
		addDefence += status[2];
		addSpeed += status[3];
		addContainerAmount += status[4];

		//�z��ɂ�����Ă���
		for (int i = 0; i < 5; ++i) {
			addStatus[i] += status[i];
		}
	}
}

void ShipParts::SetTrueStatus()
{
	for (int i = 0; i < 5; ++i) {
		trueStatus[i] = basicStatus[i] + addStatus[i];
	}
}

bool ShipParts::isClicked(int MouseX, int MouseY)
{
	//�A�C�R���摜�̕���180 �c��225
	//iconX��iconY�͕`�撆�S���W

	//iconX-90 ->iconX+90�͈͓̔��ɂ����x���W�̓A�C�R���̒��ɂ���
	//iconY-112.5 -> iconY+112.5�͈͓̔��ɂ����y���W�̓A�C�R���̒��ɂ���

	//�����A�C�R���摜���Ƀ}�E�X������A�N���b�N���Ă����
	if (gManager->isClickedRect(MouseX, MouseY, iconCenter.x - 90, iconCenter.y - 112, iconCenter.x + 90, iconCenter.y + 112)) {
		tnl::DebugTrace("\n%s�̃A�C�R���摜���N���b�N����܂���\n", factName.c_str());
		return true;
	}

	return false;
}

//�n�C���C�g���ꂽ�p�[�c�̃X�e�[�^�X��`�悷��֐�
void ShipParts::DrawPartsStatus(int TopX, int TopY)
{
	for (int i = 0; i < 5; ++i) {
		DrawStringEx(TopX, TopY + i * 20, -1, STATUSNAME[i].c_str());
		DrawStringEx(TopX + 70, TopY + i * 20, -1, "%.0f", trueStatus[i]);
	}
}

void ShipParts::DrawPartsSet()
{
	statusBack->MenuDraw();

	auto pos = statusBack->GetTopPos();
	DrawPartsStatus(pos.x + 10, pos.y + 10);

	auto modPos = modNameBack->GetTopPos();

	modNameBack->MenuDraw();
	DrawStringEx(modPos.x + 10, modPos.y + 10, -1, "����MOD");
	if (myMods.empty()) {

		DrawStringEx(modPos.x + 10, modPos.y + 30, -1, "����");
		return;
	}

	for (int i = 0; i < myMods.size(); ++i) {
		auto name = myMods[i]->GetModName();
		DrawStringEx(modPos.x + 10, modPos.y + 30 + i * 20, -1, name.c_str());
	}


}
