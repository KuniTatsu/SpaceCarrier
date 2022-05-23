#pragma once
#include"Scene.h"
#include<memory>
#include<list>
#include<vector>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class BulletManager;
class EnemyManager;
class Object;
class Player;
class Enemy;
class Factory;
class Animation;

class InGameScene :public BaseScene
{
public:
	InGameScene();
	~InGameScene();

	void Update();
	void Draw();

private:

	void Init();
	GameManager* gManager = nullptr;
	BulletManager* bManager = nullptr;
	EnemyManager* eManager = nullptr;


	//enemy���X�g
	std::list<std::shared_ptr<Enemy>>enemyList;

	std::shared_ptr<Player>player = nullptr;

	//obj�t�@�N�g���[�|�C���^
	Factory* fac = nullptr;

	//--------------�V�[�N�G���X�֌W----------------//
	tnl::Sequence<InGameScene>mainSeqence =
		tnl::Sequence<InGameScene>(this, &InGameScene::SeqCruize);

	//���q�V�[�N�G���X
	bool SeqCruize(const float deltatime);
	//�S�[���ナ�U���g�V�[�N�G���X
	bool SeqGoalResalt(const float deltatime);



	//�V�[�N�G���X�̗񋓑�
	enum class sequence {
		CRUIZE,
		GOALRESALT,
		MAX

	};
	sequence nowSeq = sequence::CRUIZE;
	sequence lastSeq = sequence::CRUIZE;

	//Sequence���ړ�������֐�,enum���ꏏ�ɕύX����
	void ChangeSequence(const sequence seq);
	//----------------------------------------------//

	//--------------�X�e�[�W�i���֌W----------------//

	//�ړ����[���̎��
	enum class LANE {
		NORMALSPEED,//�ړ����x*1.0 �G�̋������W��
		CRUISESPEED,//�ړ����x*1.5 �G�̋���*1.5
		HYPERSPEED,//�ړ����x*2.0  �G�̋���*2.0
		MAX
	};
	//���݂̑I�����[��
	LANE myLane = LANE::NORMALSPEED;
	//���[�����Ƃ̏��q���x���[�g
	const float LANEEXRATIO[static_cast<int>(LANE::MAX)]{ 1.0,1.5,2.0 };

	//�v���C���[�̏��q���x���擾
	float PlayerSpeed = 0.0f;
	//�׏d���̎擾
	float CapacityRate = 0.0f;

	//�X�e�[�W�̒���
	float stageLength = 0.0f;

	//�X�e�[�W�̌��ݒn
	float nowStayPos = 0.0f;

	//�X�e�[�W�i�s�x
	double progress = 0;

	//�X�e�[�W���̏��q�֐� �X�^�[�g����S�[���Ɉړ�����֐�
	bool Cruize();

	//�X�e�[�W�̐i���󋵂̃��Z�b�g
	void ResetStageProgress();

	//------------------------------------//
	//-------------�w�i�֌W---------------//

	//�O���t�B�b�N�n���h��
	int backGroundGh = 0;

	//test
	int testGh = 0;
	//�w�i�̕`����W���S
	tnl::Vector3 backGroundPos = {};
	//�w�i�摜�̑傫��
	const int SIZEY = 960;

	//�w�i�摜�X�N���[��
	void MoveBackGround();

	//------------------------------------//

	//-------------UI�֌W---------------//
	//�X�e�[�W�i�s�Q�[�W�̌��摜
	int stageGaugeBase = 0;
	//�X�e�[�W�i�s�Q�[�W��Fill�摜
	int stageGaugeFill = 0;

	//�S�[���摜
	int goalTestGh = 0;

	//�i�s�Q�[�W�̕`��
	void DrawProgressGauge();
	//------------------------------------//

	//-------------�G�t�F�N�g�֌W------------//
	//��ʓ��ɐ����Ă���G�t�F�N�g���X�g
	std::list<std::shared_ptr<Animation>>liveAnimationList;

	//�A�j���[�V��������
	void MakeAnimation(std::string Gh, tnl::Vector3 Pos, int ActSpeed, int MaxIndex, int XNum, int YNum, int XSize, int YSize);
	//�A�j���[�V�����X�V
	void UpdateAnimation();
	//�A�j���[�V�����`��
	void DrawAnimation();
	//�A�j���[�V�����j��
	void DeleteAnimation();

	//---------------------------------------//

	//���ׂĂ̓G�̒�������player�ɋ߂��G��I�Ԋ֐�
	std::shared_ptr<Enemy>GetNearestEnemy();

	//�G��|�����t���O
	bool isDestroyEnemy = false;

	//�I�u�W�F�N�g���X�g
	//std::list<std::shared_ptr<Object>> objectList;

};

