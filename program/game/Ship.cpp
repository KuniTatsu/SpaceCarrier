#include "Ship.h"
#include"ShipParts/ShipParts.h"
#include"Manager/PartsManager.h"

Ship::Ship()
{
	ShipInit();
}

Ship::~Ship()
{
}

void Ship::ShipInit()
{
	//�p�[�c�}�l�[�W���擾
	pManager = PartsManager::Instance();

	//�D�̏����p�[�c��o�^����
	pManager->SetProtoTypeParts(shipParts);
	//�D�̏��������o�^����
	pManager->SetProtoTypeWeapon(weapones);

	//�D�̃X�e�[�^�X�e�퍇�v���擾
	SetShipStatus();
}

void Ship::SetShipStatus()
{
	//���̑D�̃X�e�[�^�X����U�S��0�ɂ���
	ClearShipStatus();

	//�e�p�[�c�̊�{�X�e�[�^�X�z����擾����

	//�e�p�[�c�̊�{�X�e�[�^�X�z�񂪓������z��:�񎟌��z��
	float* partsStatus[5] = {};
	for (int i = 0; i < shipParts.size(); ++i) {
		partsStatus[i] = std::dynamic_pointer_cast<ShipParts, PartsBase>(shipParts[i])->GetPartsStatus();
	}

	//�񎟌��z��̊e�z��ԍ����Ƃɑ����đD�̃X�e�[�^�X�ɑ������
	//�p�[�c����
	for (int i = 0; i < 5; ++i) {
		//�e�X�e�[�^�X
		for (int k = 0; k < 5; ++k) {
			shipStatus[k] += partsStatus[i][k];
		}
	}

}

void Ship::ClearShipStatus()
{
	for (int i = 0; i < 5; ++i) {
		shipStatus[i] = 0;
	}
}

void Ship::ShootShipWeapon()
{
}
