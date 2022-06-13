#pragma once
#include<vector>
#include<memory>
#include<tuple>
#include"PartsBase.h"
#include"../../dxlib_ext/dxlib_ext.h"

class Mod;
class Menu;

class ShipParts :public PartsBase
{
public:
	//id(int)	PartsType(int)	Parts_Name	HP(float)	Atack(float)	Defence(float)	Speed(float)	Gh(std::string)	ContainerAmount
	ShipParts(int Id, int PartsType, std::string Name, float Hp, float Energy, float Defence, float Speed, std::string GhPass, std::string IconPass, float ContainerAmount);
	~ShipParts();

	//�D������ʂł̕`��֐�
	void DrawParts(int X, int Y);

	//�D������ʂł̃A�C�R���`��
	void DrawPartsIcon(int X, int Y);

	//��{�X�e�[�^�X�擾�֐�
	inline float* GetPartsStatus() {
		return basicStatus;
	}

	//�p�[�c�̃X�e�[�^�X�S�Ă���C�ɓn���Ă݂���
	inline std::tuple<int, int, std::string, float*>GetAllPartsData() {
		return{ partsId, partsType, partsName, basicStatus };
	}

	//�`��p�[�c���̎擾�֐�
	inline std::string& GetFactName() {
		return factName;
	}
	//�C��Mod���擾����֐�
	inline const std::vector<std::shared_ptr<Mod>>& GetPartsMod() {
		return myMods;
	}


	//�C���X�e�[�^�X���܂߂��p�[�c�̃X�e�[�^�X�擾
	inline float* GetTrueStatus() {
		return trueStatus;
	}
	//�A�C�R���摜���N���b�N���ꂽ��true��Ԃ��֐�
	bool isClicked(int MouseX, int MouseY);


	//�p�[�c�X�e�[�^�X��`�悷��
	void DrawPartsStatus(int TopX, int TopY);

	//�p�[�c�X�e�[�^�X�Ɣw�i�摜�̕`��
	void DrawPartsSet();

	//���O�̕�����̒������擾����֐�
	inline int& GetStrLength() {
		return strWidth;
	}

	//������Ԃ�؂�ւ���֐�
	inline void	ChangeEquiped() {
		//�������Ă�����
		if (isEquiped)
		{
			//������Ԃ��O��
			isEquiped = false;
			return;
		}
		isEquiped = true;
	}


	//�����󋵂�Ԃ��֐�
	inline bool IsEquiped() {
		return isEquiped;
	}

	//�A�C�R���摜�̕`�撆�S��Ԃ��֐�
	inline const tnl::Vector3& GetIconCenter() {
		return iconCenter;
	}

	//�J�[�\������ɂ��锻��
	bool isCursored = false;

private:

	std::shared_ptr<Menu>statusBack = nullptr;

	std::shared_ptr<Menu>modNameBack = nullptr;

	//-------------��{�X�e�[�^�X-------------//
	const std::string STATUSNAME[5] = { "�̗�","�d��","�h���","���x","�ݕ��e��" };

	//�p�[�c�̒ǉ��̗�
	float hp = 0;
	//�p�[�c�̕K�v�d��
	float energy = 0;
	//�p�[�c�̒ǉ��h���
	float defence = 0;
	//�p�[�c�̒ǉ����x
	float speed = 0;
	//�p�[�c�̒ǉ��ύډ\��
	float containerAmount = 0;

	//hp,energy,def,speed,container
	float basicStatus[5] = { 0,0,0,0,0 };

	//-----------------------------------------//

	//�C���X�e�[�^�X���v�����߂�֐�
	void SetEditStatus();
	//--------------�C���X�e�[�^�X���v----------//
	//�ǉ��̗�
	float addHp = 0;
	//�K�v�d��
	float addEnergy = 0;
	//�ǉ��h���
	float addDefence = 0;
	//�ǉ����x
	float addSpeed = 0;
	//�ǉ��ύډ\��
	float addContainerAmount = 0;

	//hp,energy,def,speed,container
	float addStatus[5] = { 0,0,0,0,0 };

	//--------------------------------------------//

	//�D�̍��v�X�e�[�^�X�����߂�֐�
	void SetTrueStatus();
	//�D�̍��v�X�e�[�^�X
	float trueStatus[5] = {};

	//�C���X�e�[�^�X���܂߂��p�[�c��
	std::string factName = "";

	//���O�̕�����̒���
	int strWidth = 0;

	//�����C���X�e�[�^�X
	std::vector<std::shared_ptr<Mod>>myMods;


	//�A�C�R���摜�̕`�撆�S���W
	int iconX = 0;
	int iconY = 0;

	tnl::Vector3 iconCenter = {};

	//�A�C�R���}�E�X���m�e�X�g�摜
	int highRight = 0;

};
