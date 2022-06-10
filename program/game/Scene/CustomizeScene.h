//�D������������ו���ύڂ����肷��V�[��

#pragma once
#include"Scene.h"
#include"../Manager/GameManager.h"
#include<memory>
#include<vector>
#include<functional>

class Player;
class ShipParts;

class CustomizeScene :public BaseScene
{
public:
	CustomizeScene();
	~CustomizeScene();

	void Update();
	void Draw();

private:
	//player�̃C���X�^���X
	std::shared_ptr<Player>player = nullptr;
	//GameManager�̃C���X�^���X
	GameManager* gManager = nullptr;


	//�������֐�
	void Init();

	//�C���x���g���ŃN���b�N�����Ƃ��Ƀp�[�c���w�肵���ۂ̓��ꕨ
	std::shared_ptr<ShipParts> selectedParts = nullptr;


	//--------------�V�[�N�G���X�֌W----------------//
	tnl::Sequence<CustomizeScene>mainSeqence =
		tnl::Sequence<CustomizeScene>(this, &CustomizeScene::SeqTop);

	//�J�X�^�}�C�Y�V�[���̃g�b�v�y�[�W�V�[�N�G���X
	bool SeqTop(const float deltatime);
	//�I���V�[�N�G���X
	bool SeqSelect(const float deltatime);
	//�D�����V�[�N�G���X
	bool SeqShipCustomize(const float deltatime);
	//����I���V�[�N�G���X
	bool SeqWeaponCustomize(const float deltatime);



	//�V�[�N�G���X�̗񋓑�
	enum class sequence :uint32_t {
		TOP,
		SELECT,
		SHIPCUSTOM,
		WEAPONCUSTOM,
		MAX

	};
	//top���j���[�����ԍۂ̃��j���[�ԍ�
	sequence SEQ[2] = { sequence::SELECT,sequence::WEAPONCUSTOM };

	//���̃V�[�N�G���X
	sequence nowSeq = sequence::TOP;
	//��O�̃V�[�N�G���X
	sequence lastSeq = sequence::TOP;

	//Sequence���ړ�������֐�,enum���ꏏ�ɕύX����
	void ChangeSequence(const sequence seq);


	//�V�[�N�G���X���̕`��֐�

	//�g�b�v�V�[�N�G���X�݂̂̕`��
	void DrawTopSeq();
	//�Z���N�g�V�[�N�G���X�݂̂̕`��
	void DrawSelectSeq();
	//�D�J�X�^�}�C�Y�V�[���݂̂̕`��
	void DrawCustomSeq();
	//����J�X�^�}�C�Y�V�[���݂̂̕`��
	void DrawWeaponSeq();

	//���̃V�[�N�G���X�ł̂ݕ`�悵�����֐�������t�@���N�V����
	std::function< void(CustomizeScene*) > drawFunc = &CustomizeScene::DrawTopSeq;


	//----------------------------------------------//

	//---------------�摜�n���h��-------------------//

	std::vector<int>ghs = {};

	//---top�V�[�N�G���X��menu�摜
	int menuShipCustomGh = 0;
	int menuWeaponCustomGh = 0;
	int menuReturnGh = 0;
	//---

	//top�V�[�N�G���X��menu�摜�T�C�Y
	const int GRAPHICSIZE = 240;

	//top�V�[�N�G���X��menu�摜�`�撆�S���W
	const tnl::Vector3 GRAPHICCENTER[3] = { tnl::Vector3(200,580,0),tnl::Vector3(520,580,0),tnl::Vector3(840,580,0) };
	
	//�w�i�摜
	int background = 0;
	//menu�n�C���C�g�摜
	int highright = 0;

	//-----------------------------------------------//
};

