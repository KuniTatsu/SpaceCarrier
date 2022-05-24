#pragma once
#include<string>

class GameManager;
class PartsBase
{
public:
	PartsBase() {};
	virtual ~PartsBase() {};

	//�p�[�cId�擾
	inline int GetPartsId() {
		return partsId;
	}
	//�p�[�c�^�C�v�擾
	inline int GetPartsType() {
		return partsType;
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

	//gh
	int gh = 0;

	//�Q�[���}�l�[�W���|�C���^
	GameManager* gManager = nullptr;
};

