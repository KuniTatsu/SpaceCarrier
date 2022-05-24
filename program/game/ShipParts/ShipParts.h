#pragma once
#include"PartsBase.h"

class ShipParts:public PartsBase
{
public:
	//id(int)	PartsType(int)	Parts_Name	HP(float)	Atack(float)	Defence(float)	Speed(float)	Gh(std::string)	ContainerAmount
	ShipParts(int Id, int PartsType, std::string Name,float Hp, float Attack, float Defence,float Speed,std::string GhPass,float ContainerAmount);
	~ShipParts();

	//�D������ʂł̕`��֐�
	void DrawParts(int X, int Y);

private:
	//�p�[�c�̒ǉ��̗�
	float hp = 0;
	//�p�[�c�̒ǉ��U����
	float attack = 0;
	//�p�[�c�̒ǉ��h���
	float defence = 0;
	//�p�[�c�̒ǉ����x
	float speed = 0;
	//�p�[�c�̒ǉ��ύډ\��
	float containerAmount = 0;

	float basicStatus[4] = {};

};
