#pragma once
#include<vector>
#include<string>
#include<memory>

class Mod;

class ModManager
{
public:
	//�C���X�^���X���Ȃ���ΐ����A����ΕԂ��֐�
	static ModManager* Instance();

	//������
	void Init();

	//�E�F�C�g����t�^����mod�����肷�郉���_���֐�
	std::unique_ptr<Mod>& GetRandomMod();
protected:
	ModManager();
	~ModManager();

private:
	//�V���O���g���C���X�^���X
	static ModManager* instance;

	//���A���e�B
	enum class RARITY :uint32_t {
		JUNK,
		NORMAL,
		RARE,
		LEGEND,
		MAX
	};

	//csv���[�h�֐�
	void LoadModCsv();

	//csv����ǂݍ��񂾐��f�[�^
	std::vector<std::vector<std::string>>loadMods;
	//���A���e�B���Ƃɕ�����ꂽ�}�X�^�[�f�[�^
	std::vector < std::vector<std::unique_ptr<Mod>>>modMaster;

	//���A���e�B�̃E�F�C�g
	int rarityWeight[static_cast<uint32_t>(RARITY::MAX)];

	//Mod�̃E�F�C�g
	std::vector<int>modWeight;




};

