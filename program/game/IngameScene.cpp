#include "InGameScene.h"
#include"Manager/BulletManager.h"
#include"Manager/EnemyManager.h"
#include"Object/Bullet.h"
#include"GameManager.h"
#include"Object/Object.h"
#include"Object/Player.h"
#include"Factory.h"
#include<time.h>
#include"Object/Enemy.h"

InGameScene::InGameScene()
{
	Init();
}

InGameScene::~InGameScene()
{
}

void InGameScene::Update()
{
	mainSeqence.update(gManager->deltatime);


}

void InGameScene::Draw()
{
	//�ꖇ�ڂ̔w�i�摜
	DrawRotaGraph(backGroundPos.x, backGroundPos.y, 2, 0, backGroundGh, false);
	DrawRotaGraph(backGroundPos.x, backGroundPos.y - SIZEY, 2, 0, testGh, false);

	auto objectList = gManager->GetObjectList();
	auto itr = objectList.begin();

	for (int i = 0; i < objectList.size(); ++i) {
		(*itr)->Draw();
		++itr;
	}

	DrawProgressGauge();

	if (nowSeq == sequence::GOALRESALT) {
		gManager->DrawRotaGraphNormal(gManager->Center.x, gManager->Center.y, goalTestGh, false);
	}
}

void InGameScene::Init()
{
	gManager = GameManager::Instance();
	bManager = BulletManager::Instance();
	eManager = EnemyManager::Instance();

	backGroundGh = gManager->LoadGraphEx("graphics/space.jpg");
	testGh = gManager->LoadGraphEx("graphics/space.jpg");

	stageGaugeBase = gManager->LoadGraphEx("graphics/StageGauge_None.png");
	stageGaugeFill = gManager->LoadGraphEx("graphics/StageGauge_Fill.png");

	goalTestGh = gManager->LoadGraphEx("graphics/TestGoal.png");

	backGroundPos = { gManager->Center.x,gManager->Center.y,0 };
	//objectList = gManager->GetObjectList();
	//player = gManager->GetPlayer();

	//�v���C���[�̐���
	player = std::make_shared<Player>();
	player->SetList();

	//�v���C���[�̏��q���x���擾
	PlayerSpeed = player->GetCruizeSpeed();
	//�׏d���̎擾
	CapacityRate = player->GetCapaciryRate();

	fac = gManager->GetFactory();

	stageLength = gManager->GetStageLength();


}

bool InGameScene::SeqCruize(const float deltatime)
{
	//�w�i�ړ�
	MoveBackGround();

	//�X�e�[�W�i���X�V
	//�����S�[���ɂ�����true���A��
	if (Cruize()) {
		//���ׂĂ̓G�ƒe�����X�g�����������
		//�C���X�^���X����
		bManager->ResetBulletList();
		bManager->ResetEnemyBulletList();
		eManager->ResetEnemyList();
		gManager->ResetObjectList();

		ChangeSequence(sequence::GOALRESALT);
		return true;
	}

	//�G�̐����@������EnemyManager����ă}�X�^�[�f�[�^����Enemy�̎�ނ�����,��������
	if (GetRand(100) % 100 > 98) {
		auto enemy = std::dynamic_pointer_cast<Enemy, Object>(fac->create("Enemy", gManager->GetRandomPos(),
			tnl::Vector3(0, 2, 0), Factory::MOVETYPE::STRAIGHT, Factory::SHOOTTYPE::STRAIGHT));
		enemy->SetList();
		enemy->SetEnemyList();
	}


	//space�L�[����������e�𔭎˂���
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_SPACE))player->ShootBullet();

	//�I�u�W�F�N�g���X�g�̃A�b�v�f�[�g
	{
		auto list = gManager->GetObjectList();
		auto it = list.begin();

		while (it != list.end()) {
			(*it)->Update();
			it++;
		}
	}
	//�e�ƃG�l�~�[�̓����蔻��
	for (auto enemy : eManager->GetList()) {
		for (auto bullet : bManager->GetList()) {
			if (tnl::IsIntersectSphere(enemy->GetPos(), enemy->GetRadius(), bullet->GetPos(), bullet->GetRadius())) {
				enemy->SetIsLive();
				bullet->SetIsLive();
			}
		}
	}
	//�C���X�^���X����
	bManager->RemoveBulletList();
	eManager->RemoveEnemyList();
	gManager->RemoveObjectList();

	return true;
}
//�S�[�����U���g�`��V�[�N�G���X
bool InGameScene::SeqGoalResalt(const float deltatime)
{
	//����Enter����������ŏ�����X�^�[�g����
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) {
		//�X�e�[�W�̐i���󋵂����Z�b�g����
		ResetStageProgress();

		//�v���C���[�̐���
		player = std::make_shared<Player>();
		player->SetList();

		ChangeSequence(sequence::CRUIZE);
		return true;
	}
	return true;
}
//�V�[�N�G���X��ύX����֐�
void InGameScene::ChangeSequence(const sequence seq)
{
	lastSeq = nowSeq;
	nowSeq = seq;

	switch (seq)
	{
	case sequence::CRUIZE: {
		mainSeqence.change(&InGameScene::SeqCruize);
		break;
	}
	case sequence::GOALRESALT: {
		mainSeqence.change(&InGameScene::SeqGoalResalt);
		break;
	}
	default:
		break;
	}
}
void InGameScene::MoveBackGround()
{
	backGroundPos.y += 5;
	//��ʉ��[�ɉ摜�̏�[���ړ�������
	if (backGroundPos.y - 480 >= 768) {
		//���ɖ߂� ���摜�T�C�Y�Ɖ�ʃT�C�Y�̍�������
		backGroundPos.y = gManager->Center.y - 72;
	}
}

bool InGameScene::Cruize()
{
	//��b�Ői�ދ������擾 ���q���x�Ɖ׏d��,���[���␳���������l����Z
	//�׏d���͋t����������(�y��(1����)�Ƒ����Ȃ�A�d��(1�ȏ�)�ƒx���Ȃ�)
	float addCruizeDistance = 0;
	//�׏d����0�̏ꍇ�͖�������
	if (CapacityRate == 0) {
		addCruizeDistance = (PlayerSpeed * LANEEXRATIO[static_cast<int>(myLane)]);
	}
	else {
		addCruizeDistance = (PlayerSpeed * LANEEXRATIO[static_cast<int>(myLane)]) / CapacityRate;
	}

	//progress��1�ɂȂ��Ă���Ή��Z���Ȃ�
	if (progress >= 1.0)return true;
	//���ݒn�ɉ��Z����
	//nowStayPos += addCruizeDistance * gManager->deltatime;

	//debug
	nowStayPos += addCruizeDistance * gManager->deltatime * 10;

	//�X�e�[�W�̐i�����X�V
	progress = static_cast<double>(nowStayPos / stageLength);
	//debug
	//tnl::DebugTrace("\n%.2f\n", progress);

	return false;
}

void InGameScene::DrawProgressGauge()
{
	//�X�e�[�W�i�s�Q�[�W�̕`��
	DrawRotaGraph(1024 - 25, gManager->Center.y, 1, 0, stageGaugeBase, true);
	//���݂̐i�s�x�ɉ����ăQ�[�W�̒�����`��
	DrawRotaGraph3(1024, 768 - 5, 50, 768, 1, progress, 0, stageGaugeFill, true);
}

void InGameScene::ResetStageProgress()
{
	nowStayPos = 0.0f;
	progress = 0.0f;

	player->SetPos(gManager->Center);
}
