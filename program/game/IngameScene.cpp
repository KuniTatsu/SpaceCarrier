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
	//�w�i�ړ�
	MoveBackGround();
	//�X�e�[�W�i���X�V
	Cruize();

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

	//tnl::IsIntersectSphere()

	//�C���X�^���X����
	bManager->RemoveBulletList();
	eManager->RemoveEnemyList();
	gManager->RemoveObjectList();
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

	backGroundPos = { gManager->Center.x,gManager->Center.y,0 };
	//objectList = gManager->GetObjectList();
	player = gManager->GetPlayer();

	fac = gManager->GetFactory();

	stageLength = gManager->GetStageLength();


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

void InGameScene::Cruize()
{
	//�v���C���[�̏��q���x���擾
	const float PLAYERSPEED = player->GetCruizeSpeed();
	//�׏d���̎擾
	const float CAPACITYRATE = player->GetCapaciryRate();

	//��b�Ői�ދ������擾 ���q���x�Ɖ׏d��,���[���␳���������l����Z
	//�׏d���͋t����������(�y��(1����)�Ƒ����Ȃ�A�d��(1�ȏ�)�ƒx���Ȃ�)
	float addCruizeDistance = 0;
	//�׏d����0�̏ꍇ�͖�������
	if (CAPACITYRATE == 0) {
		addCruizeDistance = (PLAYERSPEED * LANEEXRATIO[static_cast<int>(myLane)]);
	}
	else {
		addCruizeDistance = (PLAYERSPEED * LANEEXRATIO[static_cast<int>(myLane)]) / CAPACITYRATE;
	}

	//progress��1�ɂȂ��Ă���Ή��Z���Ȃ�
	if (progress >= 1.0)return;
	//���ݒn�ɉ��Z����
	nowStayPos += addCruizeDistance *gManager->deltatime;

	//debug
	//nowStayPos += addCruizeDistance *gManager->deltatime*3;

	//�X�e�[�W�̐i�����X�V
	progress = static_cast<double>(nowStayPos / stageLength);
}

void InGameScene::DrawProgressGauge()
{
	//�X�e�[�W�i�s�Q�[�W�̕`��5
	DrawRotaGraph(1024 - 25, gManager->Center.y, 1, 0, stageGaugeBase, true);
	//���݂̐i�s�x�ɉ����ăQ�[�W�̒�����`��
	DrawRotaGraph3(1024, 768-5, 50, 768, 1, progress, 0, stageGaugeFill, true);

	tnl::DebugTrace("\n%.2f\n", progress);
}
