#pragma once
#include"PartsBase.h"

class ShipParts :public PartsBase
{
public:
	//id(int)	PartsType(int)	Parts_Name	HP(float)	Atack(float)	Defence(float)	Speed(float)	Gh(std::string)	ContainerAmount
	ShipParts(int Id, int PartsType, std::string Name, float Hp, float Energy, float Defence, float Speed, std::string GhPass, float ContainerAmount);
	~ShipParts();

	//�D������ʂł̕`��֐�
	void DrawParts(int X, int Y);

	//��{�X�e�[�^�X�擾�֐�
	inline float* GetPartsStatus() {
		return basicStatus;
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

};
