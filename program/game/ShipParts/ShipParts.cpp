#include "ShipParts.h"
#include"../Manager/GameManager.h"
#include"../Manager/ModManager.h"
#include"../Mod.h"

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

	hoge = gManager->LoadGraphEx("graphics/ShipParts/Icon_Back_test.png");

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
		return;
	}

	//modNum�̌���mod��t�^����
	for (int i = 0; i <= modNum; ++i) {
		auto mod = mManager->CreateNewMod();
		myMods.emplace_back(mod);
		tnl::DebugTrace("\n�C��Mod[%s]��t�^���܂���\n", mod->GetModName().c_str());
	}
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
	//-----------debug--------------
	if (gManager->mousePosX>=X-90&& gManager->mousePosX <= X + 90&&
			gManager->mousePosY>=Y-112&& gManager->mousePosY <= Y + 112
		) {
		DrawRotaGraph(X, Y, 1.5, 0, hoge, false);
	}
	//-----------------------------

	DrawRotaGraph(X, Y, 1.5, 0, iconBachGh, true);
	DrawRotaGraph(X, Y, 1.5, 0, iconGh, false);

	iconX = X;
	iconY = Y;

}

bool ShipParts::isClicked(int MouseX, int MouseY)
{
	//�A�C�R���摜�̕���180 �c��225
	//iconX��iconY�͕`�撆�S���W

	//iconX-90 ->iconX+90�͈͓̔��ɂ����x���W�̓A�C�R���̒��ɂ���
	//iconY-112.5 -> iconY+112.5�͈͓̔��ɂ����y���W�̓A�C�R���̒��ɂ���

	//�����A�C�R���摜���Ƀ}�E�X������A�N���b�N���Ă����
	if (gManager->isClickedRect(MouseX, MouseY, iconX - 90, iconY - 112, iconX + 90, iconY + 112)) {
		tnl::DebugTrace("\n%s�̃A�C�R���摜���N���b�N����܂���\n", factName.c_str());
		return true;
	}

	return false;
}
