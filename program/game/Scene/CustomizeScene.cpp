#include "CustomizeScene.h"
#include"../Manager/GameManager.h"
#include"../Object/Player.h"
#include"../Manager/SceneManager.h"
#include"../Menu.h"
#include"../ShipParts/ShipParts.h"
#include"../Ship.h"

CustomizeScene::CustomizeScene()
{
	Init();
}

CustomizeScene::~CustomizeScene()
{
}

void CustomizeScene::Update()
{

	/*if (sceneChange) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
		return;
	}*/
	//�V�[�N�G���X��false���A���Ă�����V�[�����ړ�����
	if (!mainSeqence.update(gManager->deltatime)) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
	}

	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_R)) {
		SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
	}

}

void CustomizeScene::Draw()
{
	//�w�i�̕`��
	DrawRotaGraph(gManager->Center.x, gManager->Center.y, 1, 0, background, false);

	//�V�[�N�G���X���Ƃ�Draw�֐�
	drawFunc(this);


	DrawStringEx(700, 200, -1, "R�L�[�ŃX�e�[�W�Z���N�g�֖߂�");
}

void CustomizeScene::Init()
{
	gManager = GameManager::Instance();
	player = gManager->GetPlayer();

	playerShip = player->GetShip();

	menuShipCustomGh = gManager->LoadGraphEx("graphics/CustomMenu_1.png");
	menuWeaponCustomGh = gManager->LoadGraphEx("graphics/CustomMenu_2.png");
	menuReturnGh = gManager->LoadGraphEx("graphics/CustomMenu_3.png");

	ghs.emplace_back(menuShipCustomGh);
	ghs.emplace_back(menuWeaponCustomGh);
	ghs.emplace_back(menuReturnGh);

	background = gManager->LoadGraphEx("graphics/BackGroundCustomScene.png");
	highright = gManager->LoadGraphEx("graphics/CustomMenu_HighLight.png");

	partsEquipMenu = std::make_shared<SelectMenu>(400, 300, 120, 80, "graphics/FrameBlack.png");

	partsEquipMenu->AddMenuElements("��������");
	partsEquipMenu->AddMenuElements("��߂�");

}

bool CustomizeScene::SeqTop(const float deltatime)
{

	//�D�̃J�X�^�}�C�Y���N���b�N������
	//ChangeSequence(sequence::SELECT);

	//�emenu�摜�ƃ}�E�X�̔���
	for (int i = 0; i < 3; ++i) {
		if (gManager->isClickedRect(gManager->mousePosX, gManager->mousePosY, GRAPHICCENTER[i].x - (GRAPHICSIZE / 2), GRAPHICCENTER[i].y - (GRAPHICSIZE / 2),
			GRAPHICCENTER[i].x + (GRAPHICSIZE / 2), GRAPHICCENTER[i].y + (GRAPHICSIZE / 2))) {

			//�N���b�N�����̂��߂邾�����ꍇ��
			if (i == 2) {
				//SceneManager::ChangeScene(SceneManager::SCENE::SELECT);
				return false;
			}
			//����ȊO�͊e�V�[�N�G���X�ɔ��
			ChangeSequence(SEQ[i]);
		}
	}
	return true;
}

bool CustomizeScene::SeqSelect(const float deltatime)
{
	//�N���b�N������x���摜������
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		isCaution = false;
		return true;
	}

	//�����C���x���g�����̃p�[�c���N���b�N���đI��������
	if (player->InventoryUpdate(selectedParts)) {
		//���łɑ������Ă���p�[�c���N���b�N���Ă�����
		if (selectedParts->IsEquiped()) {

			//���łɑ������Ă���|��\������
			isCaution = true;
			return true;
		}

		ChangeSequence(sequence::SHIPCUSTOM);
		return true;
		//custom�V�[�N�G���X�Ɉڂ�

	}

	//�߂�{�^�����N���b�N������
	if (gManager->isClickedRect(gManager->mousePosX, gManager->mousePosY, GRAPHICCENTER[2].x - (GRAPHICSIZE / 2), GRAPHICCENTER[2].y - (GRAPHICSIZE / 2),
		GRAPHICCENTER[2].x + (GRAPHICSIZE / 2), GRAPHICCENTER[2].y + (GRAPHICSIZE / 2))) {
		ChangeSequence(sequence::TOP);
		return true;
	}
	return true;
}

bool CustomizeScene::SeqShipCustomize(const float deltatime)
{
	//menu��\��

	//��������,��߂�
	//menu�̈ړ�
	partsEquipMenu->MenuUpdate();

	//enter�L�[���������猈��,nowSelectNum�ɂ���ē����ς���
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		//----------------�����̕ύX--------------------------//
		if (partsEquipMenu->GetNowSelectNum() == 0) {
			//������ύX����
			auto type = selectedParts->GetPartsType();
			player->ChangeShipParts(type, selectedParts);

			//�p�[�c�ύX�����ʒm���o��
			//�|�b�v���b�Z�[�W�H�E�B���h�E�H

			//select�V�[�N�G���X�ɖ߂�
			ChangeSequence(sequence::SELECT);
			return true;
		}
		//-----------------select�V�[�N�G���X�ɖ߂�------------//
		else if (partsEquipMenu->GetNowSelectNum() == 1) {

			//select�V�[�N�G���X�ɖ߂�
			ChangeSequence(sequence::SELECT);

			//menu��0�ɖ߂�
			partsEquipMenu->ResetMenuNum();
			return true;
		}
	}

	//�ǂ��炩���s���܂ŃV�[�N�G���X���o�Ȃ�
	//�����������������p�[�c�^�C�v��ǂݎ��A
	//ship��changeShipParts�֐����Ă�

	//������selectedParts������

	DrawStringEx(500, 500, -1, "�J�X�^�}�C�Y�V�[�N�G���X����");
	return true;
}

bool CustomizeScene::SeqWeaponCustomize(const float deltatime)
{
	return true;
}

void CustomizeScene::ChangeSequence(const sequence seq)
{
	//���̃V�[�N�G���X�ƈ�O�̃V�[�N�G���X�����ꂼ��X�V
	lastSeq = nowSeq;
	nowSeq = seq;

	//�V�[�N�G���X��؂�ւ���
	switch (seq)
	{
	case sequence::TOP: {
		mainSeqence.change(&CustomizeScene::SeqTop);
		//�`��Ώۂ��Z���N�g�V�[���ɕύX����
		drawFunc = &CustomizeScene::DrawTopSeq;
		break;
	}
	case sequence::SELECT: {
		mainSeqence.change(&CustomizeScene::SeqSelect);
		//�`��Ώۂ��Z���N�g�V�[���ɕύX����
		drawFunc = &CustomizeScene::DrawSelectSeq;
		break;
	}
	case sequence::SHIPCUSTOM: {
		mainSeqence.change(&CustomizeScene::SeqShipCustomize);
		//�`��Ώۂ��J�X�^�}�C�Y�V�[���ɕύX����
		drawFunc = &CustomizeScene::DrawCustomSeq;
		break;
	}
	case sequence::WEAPONCUSTOM: {
		mainSeqence.change(&CustomizeScene::SeqWeaponCustomize);
		drawFunc = &CustomizeScene::DrawWeaponSeq;
		break;
	}
	default:
		break;
	}
}

void CustomizeScene::DrawTopSeq()
{

	//�emenu�摜�ƃ}�E�X�̔���
	for (int i = 0; i < 3; ++i) {
		if (gManager->OnMouseRect(gManager->mousePosX, gManager->mousePosY, GRAPHICCENTER[i].x - (GRAPHICSIZE / 2), GRAPHICCENTER[i].y - (GRAPHICSIZE / 2),
			GRAPHICCENTER[i].x + (GRAPHICSIZE / 2), GRAPHICCENTER[i].y + (GRAPHICSIZE / 2))) {
			//���j���[���n�C���C�g�\������
			DrawRotaGraph(GRAPHICCENTER[i].x, GRAPHICCENTER[i].y, 0.8, 0, highright, false);
		}
	}
	//�emenu�摜�̕`��
	int i = 0;
	for (auto gh : ghs) {
		DrawRotaGraph(200 + i * 320, 600, 0.8, 0, gh, false);
		++i;
	}
}

void CustomizeScene::DrawSelectSeq()
{
	//�p�[�c�C���x���g���̕`��
	player->DrawInventory();
	player->DrawShip();

	//�߂�{�^���̕`��ƃn�C���C�g�\��
	if (gManager->OnMouseRect(gManager->mousePosX, gManager->mousePosY, GRAPHICCENTER[2].x - (GRAPHICSIZE / 2), GRAPHICCENTER[2].y - (GRAPHICSIZE / 2),
		GRAPHICCENTER[2].x + (GRAPHICSIZE / 2), GRAPHICCENTER[2].y + (GRAPHICSIZE / 2))) {
		//���j���[���n�C���C�g�\������
		DrawRotaGraph(GRAPHICCENTER[2].x, GRAPHICCENTER[2].y, 0.8, 0, highright, false);
	}
	DrawRotaGraph(GRAPHICCENTER[2].x, GRAPHICCENTER[2].y, 0.8, 0, ghs[2], false);
}

void CustomizeScene::DrawCustomSeq()
{
	//�p�[�c�C���x���g���̕`��
	player->DrawInventory();
	player->DrawShip();

	//�����I�����j���[�̕`��
	partsEquipMenu->DrawSelectMenu();

	auto shipStatus = playerShip->GetShipStatus();

	/*for (int i = 0; i < 5; ++i) {
		DrawStringEx()
	}*/

}

void CustomizeScene::DrawWeaponSeq()
{
}
