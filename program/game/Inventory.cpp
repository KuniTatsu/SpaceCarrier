#include "Inventory.h"
#include"ShipParts/ShipParts.h"
#include"ShipParts/PartsBase.h"
#include"ShipParts/WeaponParts.h"
#include"../dxlib_ext/dxlib_ext.h"
#include"Manager/PartsManager.h"
#include"Manager/GameManager.h"
#include"GraphicUI.h"


Inventory::Inventory()
{
	pManager = PartsManager::Instance();
	gManager = GameManager::Instance();
	Init();
}

Inventory::~Inventory()
{
}

void Inventory::Init()
{
	inventoryFrameGh = gManager->LoadGraphEx("graphics/InventoryFrame.png");
}
//--------------�D�̃p�[�c���C���x���g���ɒǉ�����֐��Q-----------------------//
void Inventory::AddInventory(std::shared_ptr<ShipParts> Parts)
{
	inventory.emplace_back(Parts);
}
//�p�[�cID����C���x���g���Ƀp�[�c��ǉ�����֐�
void Inventory::AddInventory(int PartsId)
{
	auto addParts = std::dynamic_pointer_cast<ShipParts, PartsBase>(pManager->GetParts(PartsId));
	inventory.emplace_back(addParts);
}

//--------------�D�̕���p�[�c���C���x���g���ɒǉ�����֐�-------------------//
void Inventory::AddWeaponInventory(std::shared_ptr<WeaponParts> Parts)
{
	weaponInventory.emplace_back(Parts);
}

void Inventory::AddWeaponInventory(int PartsId)
{
	//auto addParts = std::dynamic_pointer_cast<WeaponParts, PartsBase>(pManager->GetWeaponParts(PartsId));
	auto addParts = std::dynamic_pointer_cast<WeaponParts, PartsBase>(pManager->GetWeaponParts(PartsId));

	weaponInventory.emplace_back(addParts);
}

void Inventory::InventoryMove()
{
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_UP)) {
		if (guideY >= 145)return;
		guideY += 10;
	}
	else if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_DOWN)) {
		guideY -= 10;
	}
}

void Inventory::InventorySelect()
{
	//auto parts = inventory.begin();

	for (auto parts : inventory) {
		parts->isClicked(gManager->mousePosX, gManager->mousePosY);
	}
}

//�C���x���g�����̃p�[�c��2��ŗ��񂵂ĕ\������֐�
void Inventory::InventoryDraw(int FrameTopX, int FrameTopY, int FrameBottomX, int FrameBottomY)
{
	//�`��͈͂����肷��(���͈͓̔�����o����`�悳��Ȃ�)
	SetDrawArea(FrameTopX, FrameTopY, FrameBottomX, FrameBottomY - 1);
	auto parts = inventory.begin();
	for (int i = 0; i < inventory.size(); ++i) {

		//���������̂��߂̕�����̒����擾
		auto length = (*parts)->GetStrLength();

		//�p�[�c���Ƃ̕`�悷��y���W �摜���m�̕���������
		int y = guideY + (i / 2) * 230;

		//GuideY�𓮂������ƂőS�Ẵp�[�c�摜�𓮂���
		//�����Ȃ獶��
		if (i % 2 == 0) {
			(*parts)->DrawPartsIcon(guideX, y);

			//�p�[�c���̕`�� (180-length/2)�͕\���\�̈�̒������W�����߂鎮
			DrawStringEx(-80 + (180 - length / 2), y - 100, GetColor(0, 0, 0), (*parts)->GetFactName().c_str());
		}
		//��Ȃ�E��
		else {
			(*parts)->DrawPartsIcon(guideX + 180, y);

			//�p�[�c���̕`��
			DrawStringEx(110 + (180 - length / 2), y - 100, GetColor(0, 0, 0), (*parts)->GetFactName().c_str());
		}

		parts++;
	}
	//�`��G���A�����ɖ߂�
	SetDrawArea(0, 0, 1024, 768);

	//�ŊO�g�̉摜�̕`��
	auto center = tnl::Vector3(FrameTopX + ((FrameBottomX - FrameTopX) / 2 - 1), FrameTopY + ((FrameBottomY - FrameTopY) / 2), 0);
	DrawRotaGraph(center.x, center.y, 1.5, 0, inventoryFrameGh, true);


}
