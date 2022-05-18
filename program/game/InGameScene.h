#pragma once
#include"Scene.h"
#include<memory>
#include<list>
#include"../dxlib_ext/dxlib_ext.h"

class GameManager;
class BulletManager;
class EnemyManager;
class Object;
class Player;
class Enemy;
class Factory;

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

	//�ړ����[���̎��
	enum class LANE {
		NORMALSPEED,//�ړ����x*1.0 �G�̋������W��
		CRUISESPEED,//�ړ����x*1.5 �G�̋���*1.5
		HYPERSPEED,//�ړ����x*2.0  �G�̋���*2.0
		MAX
	};
	//���݂̑I�����[��
	LANE myLane = LANE::NORMALSPEED;

	const float LANEEXRATIO[static_cast<int>(LANE::MAX)]{ 1.0,1.5,2.0 };

	//�X�e�[�W�̒���
	float stageLength = 0.0f;

	//�X�e�[�W�̌��ݒn
	float nowStayPos = 0.0f;

	//�X�e�[�W�i�s�x
	double progress = 0;

	//�X�e�[�W���̏��q�֐� �X�^�[�g����S�[���Ɉړ�����֐�
	void Cruize();


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

	//�i�s�Q�[�W�̕`��
	void DrawProgressGauge();
	//------------------------------------//

	//�I�u�W�F�N�g���X�g
	//std::list<std::shared_ptr<Object>> objectList;

};

