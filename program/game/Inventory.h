//�v���C���[����������A�C�e��,�p�[�c��ێ�����C���x���g���N���X
#pragma once
#include<list>
#include<memory>

class PartsBase;
class ShipParts;
class WeaponParts;

class GraphicUI;
class PartsManager;

class Inventory
{
public:
	Inventory();
	~Inventory();

	void Init();

	//inventory�ɑD�̃p�[�c��ǉ�����֐�
	void AddInventory(std::shared_ptr<ShipParts>Parts);
	void AddInventory(int PartsId);

	//inventory�ɕ���p�[�c��ǉ�����֐�
	void AddWeaponInventory(std::shared_ptr<WeaponParts>Parts);
	void AddWeaponInventory(int PartsId);

	//�D�̃p�[�c�C���x���g�����擾����֐�
	inline std::list<std::shared_ptr<ShipParts>>& GetPartsInventory() {
		return inventory;
	}

	//����C���x���g�����擾����֐�
	inline std::list<std::shared_ptr<WeaponParts>>& GetWeaponInventory() {
		return weaponInventory;
	}

	//inventory�̒��g��S�폜����֐�
	inline void CleanInventory() {
		inventory.clear();
	}
	//�C���x���g�����̃A�C�R�����X�g���X�N���[������֐�
	void InventoryMove();

	//�C���x���g�����̃A�C�R���摜��`�悷��֐�
	void InventoryDraw(int FrameTopX, int FrameTopY, int FrameBottomX, int FrameBottomY);


	//�C���x���g�����̉摜�̊�_�摜
	int guideX = 100;
	int guideY = 50;

private:
	//�D�̃p�[�c�̃C���x���g��
	std::list<std::shared_ptr<ShipParts>>inventory;

	//����p�[�c�̃C���x���g��
	std::list<std::shared_ptr<WeaponParts>>weaponInventory;

	PartsManager* pManager = nullptr;
	//�C���x���g���̔w�i�摜
	std::shared_ptr<GraphicUI>back;

	enum class DRAWINVENTORY :uint32_t {
		SHIPPARTS,
		WEAPON,
		MAX
	};



};


