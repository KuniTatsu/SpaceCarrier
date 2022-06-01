//player�̑D�̏��N���X
//�e��p�[�c�̃|�C���^������
#pragma once
#include<vector>
#include<memory>

class PartsBase;
class PartsManager;

class Ship
{
public:
	Ship();
	~Ship();

	inline const float* GetShipStatus() {
		return shipStatus;
	}

private:

	//�������֐�
	void ShipInit();

	//�p�[�c�}�l�[�W���|�C���^
	PartsManager* pManager = nullptr;

	enum class PARTS :uint32_t {
		HULL,
		CONTAINER,
		ARMOR,
		GENERATOR,
		THRUSTER,
		MAX
	};

	enum class WEAPON :uint32_t {
		MAIN,
		SUB,
		MAX
	};
	//�e�p�[�c�̃|�C���^
	//std::shared_ptr<PartsBase> shipParts[static_cast<uint32_t>(PARTS::MAX)] = { nullptr,nullptr, nullptr, nullptr, nullptr };

	std::vector < std::shared_ptr<PartsBase>>shipParts = { nullptr,nullptr, nullptr, nullptr, nullptr };

	/*std::shared_ptr<PartsBase>* GetPointa() {
		return shipParts;
	}*/

	/*
	//------�e�p�[�c�̃|�C���^---------
	//�D�̃p�[�c
	PartsBase* hull = nullptr;
	//�ݕ����p�[�c
	PartsBase* container = nullptr;
	//���b�p�[�c
	PartsBase* armor = nullptr;
	//���d�@�p�[�c
	PartsBase* generator = nullptr;
	//�X���X�^�[�p�[�c
	PartsBase* thruster = nullptr;
	*/
	/*
	//����1
	PartsBase* mainWeapon = nullptr;
	//����2
	PartsBase* subWeapon = nullptr;
	*/

	//���ڕ���z��	�����ꂢ��������𓋍ڂł���悤��vector�Ŏ���
	std::vector<std::shared_ptr<PartsBase>>weapones;

	//main���퓋�ډ\��
	int allowMainWeaponNum = 1;
	//sub���퓋�ډ\��
	int allowSubWeaponNum = 1;

	enum class STATUS :uint32_t {
		HP,
		ENERGY,
		DEFENCE,
		SPEED,
		CONTAINER,
		MAX
	};
	//���ڃp�[�c�̍��v�X�e�[�^�X hp,energy,defence,speed,container
	float shipStatus[static_cast<uint32_t>(STATUS::MAX)] = { 0,0,0,0,0 };

	//���ڃp�[�c�̊e�X�e�[�^�X���v���o���֐�
	void SetShipStatus();

	//�D�̃X�e�[�^�X�̏�����
	void ClearShipStatus();

	/*
	//-------���ڃp�[�c�̍��v�X�e�[�^�X
	//�̗�
	float hp = 0;
	//�K�v�d��
	float energy = 0;
	//�h���
	float defence = 0;
	//���x
	float speed = 0;
	//�ύډ\��
	float containerAmount = 0;
	*/

	//�D�̃p�[�c��ύX����֐�
	void ChangeShipParts(int PartsType, std::shared_ptr<PartsBase> NewParts);


	//���ڕ���S�ĂŎˌ�����֐�
	void ShootShipWeapon();

};

