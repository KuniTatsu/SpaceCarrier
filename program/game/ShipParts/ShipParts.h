#pragma once
#include<vector>
#include<memory>
#include<tuple>
#include"PartsBase.h"

class Mod;

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

	//test
	//�A�C�R���摜���N���b�N���ꂽ��true��Ԃ��֐�
	bool isClicked(int MouseX, int MouseY);

	//���O�̕�����̒������擾����֐�
	inline int& GetStrLength() {
		return strWidth;
	}

private:
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
	float basicStatus[5] = {};

	//�C���X�e�[�^�X���܂߂��p�[�c��
	std::string factName = "";

	//���O�̕�����̒���
	int strWidth = 0;

	//�����C���X�e�[�^�X
	std::vector<std::shared_ptr<Mod>>myMods;


	//�A�C�R���摜�̕`�撆�S���W
	int iconX = 0;
	int iconY = 0;

	//�A�C�R���}�E�X���m�e�X�g�摜
	int hoge = 0;

};
