//player�̑D�̏��N���X
//�e��p�[�c�̃|�C���^������
#pragma once
#include<vector>
#include<memory>

class PartsBase;
class ShipParts;
class WeaponParts;
class PartsManager;
class GameManager;

class Ship
{
public:
	Ship();
	~Ship();

	//�D�̊�{�X�e�[�^�X�擾�֐�
	inline const float* GetShipStatus() {
		return shipStatus;
	}

	//�D�̃p�[�c�̕`��֐�
	void DrawShipParts();

	//�D�̏����p�[�c�o�^�֐�
	void SetProtoParts(std::shared_ptr<ShipParts>Parts);

	//�D�̏�������o�^�֐�
	void SetProtoWeapon(std::shared_ptr<WeaponParts>Weapon);

	//���ڃp�[�c�̊e�X�e�[�^�X���v���o���֐�
	void SetShipStatus();

	//���ڕ���S�ĂŎˌ�����֐�
	void ShootShipWeapon();

	//���ڕ���S�ẴN�[���_�E���̍X�V�֐�
	void AllWeaponCoolDawnUpdate();

	//���ڕ���S�ẴN�[���_�E���擾�֐�
	float GetCoolDown(int WeaponNum);

	//�D�̌��ݑ������̕���̐���Ԃ��֐�
	inline int GetWeaponNum() {
		return weapones.size();
	}

	//�D�̃p�[�c��ύX����֐�
	void ChangeShipParts(int PartsType, std::shared_ptr<ShipParts> NewParts);

	//�D�ɑ������Ă���p�[�c�ꗗ��Ԃ��֐�
	inline const std::vector<std::shared_ptr<ShipParts>>& GetShipPartsList() {
		return shipParts;
	}

private:

	//�������֐�
	void ShipInit();

	//�p�[�c�}�l�[�W���|�C���^
	PartsManager* pManager = nullptr;
	//�Q�[���}�l�[�W���|�C���^
	GameManager* gManager = nullptr;

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

	//�D�ɑ������Ă���p�[�c
	std::vector<std::shared_ptr<ShipParts>>shipParts = {};


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
	std::vector<std::shared_ptr<WeaponParts>>weapones;

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




};

