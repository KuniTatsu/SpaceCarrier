//�Q�[���S�̂��Ǘ�����}�l�[�W���N���X
//�V���O���g���ō���Ă���
#pragma once
#include<vector>
#include<list>
#include<string>
#include<unordered_map>
#include"../../dxlib_ext/dxlib_ext.h"
#include<memory>

class SceneManager;
class FadeControl;
class Sound;
class Object;
class BulletManager;
class PartsManager;
class ModManager;
class Player;
class Factory;
class ObjectFactory;
class Observer;

class GameManager {

protected:
	GameManager();
	~GameManager();
public:
	//�C���X�^���X���Ȃ���ΐ����A����ΕԂ��֐�
	static GameManager* Instance();

	//�I�u�W�F�N�g�t�@�N�g���[�C���X�^���X
	Factory* objFac = nullptr;

	//�t�@�N�g���[�̎擾
	inline Factory* GetFactory() {
		return objFac;
	}

	int testGraphic = 0;

	//�X�e�[�W�̃��X�g
	enum class STAGE :uint32_t {
		SOL,	//�X�e�[�W1 ��Փx�� 
		AIGIS,	//�X�e�[�W2 ��Փx�� 
		ICALOS,	//�X�e�[�W3 ��Փx�ፂ
		MAX
	};

	/*
	FadeControl* fControl = nullptr;
	Sound* sound = nullptr;*/

	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;

	//�t���[���b
	float deltatime = 0.0f;

	//��ʒ������W
	const tnl::Vector3 Center = { 512,384,0 };


	void Update(const float Deltatime);
	void Draw(const float Deltatime);

	//GameManager�̏�����
	void initGameManager();

	//�摜��ǂݍ����map�ɓ����֐�
	//���łɂ���gh�Ȃ炻���Ԃ�
	int LoadGraphEx(std::string Gh);

	//�������̘A�Ȃ����摜��vector�Ɋi�[����֐�
	void LoadDivGraphEx(const std::string Gh, const int AllNum, const int WidthNum, const int HeightNum,
		int XSize, int YSize, std::vector<int>& GhVector);

	//DrawRotaGraph�̒Z�k��
	void DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag);

	//Object���X�g�̏�����
	inline void ResetObjectList() {
		objects.clear();
	}
	//Object���X�g�ւ̒ǉ�
	inline void AddObjectList(std::shared_ptr<Object> Ptr) {
		objects.emplace_back(Ptr);
	}
	//object���X�g�擾
	inline std::list<std::shared_ptr<Object>>& GetObjectList() {
		return objects;
	}
	//�v���C���[�̎擾
	inline std::shared_ptr<Player>& GetPlayer() {
		return player;
	}
	//�v���C���[�̐ݒ�
	inline void	SetPlayer(std::shared_ptr<Player> Player) {
		player = Player;
	}

	//�P�ʃx�N�g���擾�֐�
	inline tnl::Vector3 GetFixVector(float X, float Y) {

		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);

	}
	//������Pos���m�̋������擾����֐�
	inline float GetLength(tnl::Vector3 PosA, tnl::Vector3 PosB) {
		return std::sqrt(((PosA.x - PosB.x) * (PosA.x - PosB.x)) + ((PosA.y - PosB.y) * (PosA.y - PosB.y)));
	}
	//�Q�̃x�N�g���̊O�ς����߂�֐� VecA:���x�x�N�g�� VecB:�����x�N�g��
	float GetCross(tnl::Vector3 VecA, tnl::Vector3 VecB);


	//�I�u�W�F�N�g���X�g����̔r��
	void RemoveObjectList();

	int GetRandEx(int a, int b);

	const tnl::Vector3 SPAWNPOS = { 0,-50,0 };
	//��ʓ��̃����_���ȃ|�W�V�������擾����֐�
	tnl::Vector3 GetRandomPos();

	//�����Z���k�E�c�C�X�^�[���̗p�������K���z�����_���֐�
	int GerRandomNumInWeight(const std::vector<int>WeightList);


	//�X�e�[�W�ݒ�֐�
	void SetMyStage(STAGE stage) {
		mystage = stage;
	}

	//�I�������X�e�[�W�̒�����n���֐�
	inline const float GetStageLength() {
		return STAGELENGTH[static_cast<int>(mystage)];
	}

	//�l�p�`�̃}�E�X�N���b�N���m
	bool isClickedRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom);

	//�l�p�`�̃}�E�X�͈͓����m
	bool OnMouseRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom);


	//�}�E�X���W
	int mousePosX = 0;
	int mousePosY = 0;

	//�}�E�X�X�N���[��
	int mouseWheel = 0;

	//UI����ׂ����
	enum class DIR {
		HORIZONTAL,
		VERTICAL,
		MAX
	};

	//ModManager����
	void CreateModManager();

	//Observer�擾

	inline Observer* GetObserver() {
		return enemyChecker;
	}

	//�p�[�c�}�l�[�W���ǂݍ��ݏI���t���O�擾
	inline bool GetLoadedFlag() {
		return isLoaded;
	}
	//�p�[�c�}�l�[�W���ǂݍ��ݏI���t���O�Z�b�g
	inline void SetLoadedFlag(){
		isLoaded = true;
	}

	//player�����֐�
	std::shared_ptr<Player> CreatePlayer();

private:
	//�V���O���g���C���X�^���X
	static GameManager* instance;

	//BulletManager�C���X�^���X
	BulletManager* bManager = nullptr;

	//PartsManager�C���X�^���X
	PartsManager* pManager = nullptr;

	//�p�[�c�}�l�[�W���ǂݍ��݃t���O
	bool isLoaded = false;

	//ModManager�C���X�^���X
	ModManager* mManager = nullptr;

	
	
	//�I�u�U�[�o�C���X�^���X
	Observer* enemyChecker = nullptr;

	//�I�������X�e�[�W
	STAGE mystage = STAGE::SOL;
	//�X�e�[�W�̒���
	const float STAGELENGTH[static_cast<uint32_t>(STAGE::MAX)] = { 1000,1500,2000 };

	//�I�u�W�F�N�g���X�g
	std::list<std::shared_ptr<Object>> objects;

	//player�|�C���^
	std::shared_ptr<Player>player = nullptr;

	//�A�C�e������excel����ǂݎ��֐�
	void loadItem();

	std::vector<std::vector<std::string>> loadItemCsv;
};