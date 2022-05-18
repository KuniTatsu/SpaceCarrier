///*****Description*****
///�A�j���[�V�����Ɋւ���N���X
///�C���X�^���X�������ɃA�j���[�V�����̏����擾
/// ���̃A�j���[�V�����̍X�V�A�`�揈�����s��
///*********************#pragma once
#include"../dxlib_ext/dxlib_ext.h"
#include<string>
#include<vector>

class GameManager;

class Animation {
public:
	Animation() {};
	//URL,�`�撆�S,�X�V���x,�ő喇��,����������,�c��������,���摜�T�C�Y,�c�摜�T�C�Y
	Animation(std::string Gh, tnl::Vector3 Pos, int ActSpeed, int MaxIndex, int XNum, int YNum, int XSize, int YSize);
	~Animation();

	//�A�j���[�V�����X�V
	void Update();
	//�A�j���[�V�����`��
	void Draw();
	//�A�j���[�V�������I�����Ă��邩�擾����֐�
	inline bool GetIsAlive() {
		return isAlive;
	}

private:
	GameManager* gManager = nullptr;
	//�摜�n���h��
	std::vector<int>animGh = {};

	//�`����W
	tnl::Vector3 pos;
	//�R�}�X�V�t���[����
	int actSpeed = 0;
	//�R�}�ő吔
	int maxMotionIndex = 0;
	//���݂̃t���[���J�E���g
	int actWait = actSpeed;
	//�I�𒆂̉摜�C���f�b�N�X
	int actIndex = 0;
	//�`�悷��摜
	int drawGh = 0;


	//�A�j���[�V�����̏I���m�F�t���O
	bool isAlive = true;
};