#include "Ship.h"
#include"ShipParts/ShipParts.h"
#include"ShipParts/WeaponParts.h"
#include"Manager/PartsManager.h"
#include"Manager/GameManager.h"

Ship::Ship()
{
	ShipInit();
}

Ship::~Ship()
{
}

void Ship::DrawShipParts()
{
	for (auto parts : shipParts) {
		parts->DrawParts(gManager->Center.x + 50, gManager->Center.y);
	}
}

void Ship::SetProtoParts(std::shared_ptr<ShipParts>Parts)
{
	shipParts.emplace_back(Parts);
}

void Ship::SetProtoWeapon(std::shared_ptr<WeaponParts> Weapon)
{
	weapones.emplace_back(Weapon);
}

void Ship::ShipInit()
{
	//�p�[�c�}�l�[�W���擾
	pManager = PartsManager::Instance();
	gManager = GameManager::Instance();
	/*
	//�D�̏����p�[�c��o�^����
	pManager->SetProtoTypeParts(shipParts);
	//�D�̏��������o�^����
	pManager->SetProtoTypeWeapon(weapones);
	*/
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
			if (partsStatus[i] == nullptr)continue;
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
//-------�D�̃p�[�c�����֐�---------------//
void Ship::ChangeShipParts(int PartsType, std::shared_ptr<PartsBase> NewParts)
{
	//�������̃p�[�c���O��
	shipParts[PartsType] = nullptr;

	//�������Ă��銷���Ώۂ̃p�[�c�𑕔�����
	shipParts[PartsType] = NewParts;
}

void Ship::ShootShipWeapon()
{
	for (auto weapon : weapones) {
		weapon->ShootBullet(gManager->deltatime);
	}
}

void Ship::AllWeaponCoolDawnUpdate()
{
	for (auto weapon : weapones) {
		weapon->WeaponUpdate();
	}
}

float Ship::GetCoolDown(int WeaponNum)
{
	return weapones[WeaponNum]->GetWeaponCoolDawn();
}
