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
class Player;
class Factory;
class ObjectFactory;

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
	inline std::shared_ptr<Player> GetPlayer() {
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

	//�I�u�W�F�N�g���X�g����̔r��
	void RemoveObjectList();

	int GetRandEx(int a, int b);

	const tnl::Vector3 SPAWNPOS = { 0,-50,0 };
	//��ʓ��̃����_���ȃ|�W�V�������擾����֐�
	tnl::Vector3 GetRandomPos();

	//�X�e�[�W�ݒ�֐�
	void SetMyStage(STAGE stage) {
		mystage = stage;
	}

	//�I�������X�e�[�W�̒�����n���֐�
	inline const float GetStageLength() {
		return STAGELENGTH[static_cast<int>(mystage)];
	}

	//�l�p�`�̃}�E�X���m
	bool isClickedRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom);

	//�}�E�X���W
	int mousePosX = 0;
	int mousePosY = 0;

	//UI����ׂ����
	enum class DIR {
		HORIZONTAL,
		VERTICAL,
		MAX
	};

private:
	//�V���O���g���C���X�^���X
	static GameManager* instance;

	//BulletManager�C���X�^���X
	BulletManager* bManager = nullptr;

	//�I�������X�e�[�W
	STAGE mystage = STAGE::SOL;
	//�X�e�[�W�̒���
	const float STAGELENGTH[static_cast<uint32_t>(STAGE::MAX)] = { 1000,1500,2000 };

	//�I�u�W�F�N�g���X�g
	std::list<std::shared_ptr<Object>> objects;

	std::shared_ptr<Player>player = nullptr;

	//�A�C�e������excel����ǂݎ��֐�
	void loadItem();

	std::vector<std::vector<std::string>> loadItemCsv;
};