//�Q�[���S�̂��Ǘ�����}�l�[�W���N���X
//�V���O���g���ō���Ă���
#pragma once
#include<vector>
#include<list>
#include<string>
#include<unordered_map>
#include"../dxlib_ext/dxlib_ext.h"
#include<memory>
#include"Object/Object.h"

class SceneManager;
class FadeControl;
class Sound;
class Object;
class BulletManager;
class Player;

class GameManager {

protected:
	GameManager();
	~GameManager();
public:
	//�C���X�^���X���Ȃ���ΐ����A����ΕԂ��֐�
	static GameManager* Instance();


	int testGraphic = 0;

	/*
	FadeControl* fControl = nullptr;
	Sound* sound = nullptr;*/

	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;

	float deitatime_ = 0;
	//��ʒ������W
	const tnl::Vector3 Center = { 512,364,0 };


	void Update();
	void Draw();

	//GameManager�̏�����
	void initGameManager();

	//�摜��ǂݍ����map�ɓ����֐�
	//���łɂ���gh�Ȃ炻���Ԃ�
	int LoadGraphEx(std::string Gh);

	//DrawRotaGraph�̒Z�k��
	void DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag);

	//Object���X�g�ւ̒ǉ�
	inline void AddObjectList(std::shared_ptr<Object> Ptr) {
		objects.emplace_back(Ptr);
	}
	//object���X�g�擾
	inline std::list<std::shared_ptr<Object>>& GetObjectList() {
		return objects;
	}

	inline std::shared_ptr<Player> GetPlayer() {
		return player;
	}

	void RemoveObjectList();


private:
	//�V���O���g���C���X�^���X
	static GameManager* instance;

	//BulletManager�C���X�^���X
	BulletManager* bManager = nullptr;

	std::list<std::shared_ptr<Object>> objects;

	std::shared_ptr<Player>player = nullptr;

	//�A�C�e������excel����ǂݎ��֐�
	void loadItem();

	std::vector<std::vector<std::string>> loadItemCsv;
};