#include "Inventory.h"
#include"ShipParts/ShipParts.h"
#include"ShipParts/PartsBase.h"
#include"../dxlib_ext/dxlib_ext.h"
#include"Manager/PartsManager.h"

Inventory::Inventory()
{
	pManager = PartsManager::Instance();
}

Inventory::~Inventory()
{
}

void Inventory::Init()
{

}

void Inventory::AddInventory(std::shared_ptr<ShipParts> Parts)
{
	inventory.emplace_back(Parts);
}
void Inventory::AddInventory(int PartsId)
{
	auto addParts = std::dynamic_pointer_cast<ShipParts, PartsBase>(pManager->GetParts(PartsId));
	inventory.emplace_back(addParts);
}
//�C���x���g�����̃p�[�c��2��ŗ��񂵂ĕ\������֐�
void Inventory::InventoryDraw(int GuideX, int GuideY, int FrameTopX, int FrameTopY, int FrameBottomX, int FrameBottomY)
{
	//�`��͈͂����肷��(���͈͓̔�����o����`�悳��Ȃ�)
	SetDrawArea(FrameTopX, FrameTopY, FrameBottomX, FrameBottomY);

	auto parts = inventory.begin();
	for (int i = 0; i < inventory.size(); ++i) {

		int y = GuideY + (i / 2) * 120;



		//GuideX��GuideY�𓮂������ƂőS�Ẵp�[�c�摜�𓮂���
		//�����Ȃ�E��
		if (i % 2 == 0) {
			(*parts)->DrawPartsIcon(GuideX + 120, y);
		}
		//��Ȃ獶��
		else {
			(*parts)->DrawPartsIcon(GuideX, y);
		}
		parts++;
	}
	//�`��G���A�����ɖ߂�
	SetDrawArea(0, 0, 1024, 768);
}
