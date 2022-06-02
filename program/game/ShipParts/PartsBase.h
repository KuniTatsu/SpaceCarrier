#pragma once
#include<string>

class GameManager;
class ModManager;
class PartsBase
{
public:
	PartsBase() {};
	virtual ~PartsBase() {};

	//�p�[�cId�擾
	inline int& GetPartsId() {
		return partsId;
	}
	//�p�[�c�^�C�v�擾
	inline int& GetPartsType() {
		return partsType;
	}
	//�p�[�c���擾
	inline std::string& GetPartsName() {
		return partsName;
	}
	//�摜�n���h���̃p�X�擾
	inline std::string& GetPartsGhPass() {
		return pass;
	}
	//�A�C�R���摜�̃p�X�擾
	inline std::string& GetIconGhPass() {
		return iconPass;
	}


	//�D������ʂł̕`��֐�
	virtual void DrawParts(int X,int Y) = 0;

protected:
	//id
	int partsId = 0;
	//�p�[�c�^�C�v
	int partsType = 0;
	//�p�[�c��
	std::string	partsName = "";

	//ghPass
	std::string pass = "";
	//gh
	int gh = 0;

	//IconGhPass
	std::string iconPass = "";
	//iconGh
	int iconGh = 0;

	//�Q�[���}�l�[�W���|�C���^
	GameManager* gManager = nullptr;

	//ModManager�|�C���^
	ModManager* mManager = nullptr;
};

