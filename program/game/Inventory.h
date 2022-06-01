//�v���C���[����������A�C�e��,�p�[�c��ێ�����C���x���g���N���X
#pragma once
#include<list>
#include<memory>

class PartsBase;
class ShipParts;

class GraphicUI;
class PartsManager;

class Inventory
{
public:
	Inventory();
	~Inventory();

	void Init();

	//inventory�ɒǉ�����֐�
	void AddInventory(std::shared_ptr<ShipParts>Parts);
	void AddInventory(int PartsId);

	//inventory�̒��g��S�폜����֐�
	inline void CleanInventory() {
		inventory.clear();
	}

	void InventoryDraw(int GuideX,int GuideY,int FrameTopX, int FrameTopY, int FrameBottomX, int FrameBottomY);

private:
	std::list<std::shared_ptr<ShipParts>>inventory;

	PartsManager* pManager = nullptr;

	std::shared_ptr<GraphicUI>back;
};


