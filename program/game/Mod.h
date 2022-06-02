//***ShipParts�ɕt���C��Mod�̃N���X***
//�p�[�c���ɖ��O���ǉ������+�\�͒l���ǉ������
#pragma once
#include<string>
#include<tuple>

class Mod
{
public:
	Mod() {};
	Mod(int Id,int Type,std::string Name,float Hp,float Energy,float Defence,float Speed,float Container);
	~Mod();

	//float�^�̊�{�X�e�[�^�X�擾�֐�
	inline float* GetBasicStatus() {
		return basicStatus;
	}
	//Mod���擾�֐�
	std::string GetModName() {
		return modName;
	}

	//ModId�擾�֐�
	inline int& GetModId() {
		return modId;
	}

	//Mod�C���X�^���X�����ɕK�v�ȃf�[�^�S�Ă�n���֐�
	inline std::tuple<int, int, std::string, float*>GetModData() {
		return { modId,modType,modName,basicStatus };
	}

private:
	//id
	int modId = 0;
	//type
	int modType = 0;
	//name
	std::string modName = "";


	//�ǉ��̗�
	float hp = 0;
	//�K�v�d��
	float energy = 0;
	//�ǉ��h���
	float defence = 0;
	//�ǉ����x
	float speed = 0;
	//�ǉ��ύډ\��
	float containerAmount = 0;

	//hp,energy,def,speed,container
	float basicStatus[5] = {};

};

