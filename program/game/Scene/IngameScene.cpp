#include "InGameScene.h"
#include"../Manager/BulletManager.h"
#include"../Manager/EnemyManager.h"
#include"../Object/Bullet.h"
#include"../Manager/GameManager.h"
#include"../Object/Object.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include"../Factory.h"
#include<time.h>
#include"../Animation.h"

InGameScene::InGameScene()
{
	Init();
}

InGameScene::~InGameScene()
{
}

void InGameScene::Update()
{
	//�A�j���[�V�����X�V
	UpdateAnimation();
	//���݂̃V�[�N�G���X�̃A�b�v�f�[�g
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
	//�A�j���[�V�����`��
	DrawAnimation();
	//�i���Q�[�W�`��
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

	//�v���C���[�̐���
	player = std::make_shared<Player>();
	player->SetList();
	gManager->SetPlayer(player);

	//�v���C���[�̏��q���x���擾
	PlayerSpeed = player->GetCruizeSpeed();
	//�׏d���̎擾
	CapacityRate = player->GetCapaciryRate();
	//�I�u�W�F�N�g�t�@�N�g���[�̎擾
	fac = gManager->GetFactory();
	fac->GetEnemyManager();
	//�X�e�[�W�̒����̎擾
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
		//-----�C���X�^���X����-------
		bManager->ResetBulletList();
		bManager->ResetEnemyBulletList();
		eManager->ResetEnemyList();
		gManager->ResetObjectList();
		//----------------------------
		//���U���g�V�[�N�G���X�ɔ��
		ChangeSequence(sequence::GOALRESALT);
		return true;
	}

	//�G�̐����@������EnemyManager����ă}�X�^�[�f�[�^����Enemy�̎�ނ�����,�������� eManager->CreateEnemy("NORMAL",startpos,vpos);
	if (GetRand(100) % 100 > 98) {
		/*auto enemy = std::dynamic_pointer_cast<Enemy, Object>(fac->create("Enemy", gManager->GetRandomPos(),
			tnl::Vector3(0, 2, 0), Factory::MOVETYPE::STOPPOS , Factory::SHOOTTYPE::STRAIGHT));*/

		auto enemy = eManager->CreateEnemy(EnemyManager::ENEMYTYPE::NORMAL, gManager->GetRandomPos(), tnl::Vector3(0, 2, 0));
		enemy->SetList();
		enemy->SetEnemyList();

	}

	//TAB�����������ԋ߂��̓G���I�[�g�^�[�Q�b�g����
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_TAB)) {
		//player�����ԋ߂��G���I�[�g�^�[�Q�b�g�ڕW�Ƃ��ēo�^
		player->SetMyTarget(GetNearestEnemy());

		//�I�[�g�^�[�Q�b�g�̍X�V��L���ɂ���
		player->ChageAutoTargerMode();
	}
	//�^�[�Q�b�g���ݒ肳��Ă���΃I�[�g�^�[�Q�b�g�ˌ����\
	//space�L�[����������e�𔭎˂���
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_SPACE)) {
		if (player->isAutoTargetMode()) {
			player->AimShootBullet();
		}
		player->ShootBullet();
	}

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
				//�A�j���[�V�����𐶐�����
				MakeAnimation("graphics/Explosion.png", enemy->GetPos(), 10, 7, 7, 1, 120, 120);
				//�G�ƒe�����S��Ԃɂ���
				enemy->SetIsLive();
				bullet->SetIsLive();
				isDestroyEnemy = true;
			}
		}
	}
	//�C���X�^���X����
	bManager->RemoveBulletList();
	eManager->RemoveEnemyList();
	gManager->RemoveObjectList();

	if (isDestroyEnemy) {

		isDestroyEnemy = false;
		//�I�[�g�^�[�Q�b�g��ON�Ȃ玟�̃^�[�Q�b�g��o�^����
		if (!player->isAutoTargetMode())return true;

		//�^�[�Q�b�g������
		player->CleanTarget();
		//player�����ԋ߂��G���I�[�g�^�[�Q�b�g�ڕW�Ƃ��ēo�^
		player->SetMyTarget(GetNearestEnemy());


	}

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
	//���̃V�[�N�G���X�ƈ�O�̃V�[�N�G���X�����ꂼ��X�V
	lastSeq = nowSeq;
	nowSeq = seq;

	//�V�[�N�G���X��؂�ւ���
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
	nowStayPos += addCruizeDistance * gManager->deltatime;

	//debug
	//nowStayPos += addCruizeDistance * gManager->deltatime * 10;

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
	//�����ʒu�Ƀ��Z�b�g
	nowStayPos = 0.0f;
	//�i����0�Ƀ��Z�b�g
	progress = 0.0f;
	//player�̕`����W����ʒ��S�Ɉړ�
	player->SetPos(gManager->Center);
}

void InGameScene::MakeAnimation(std::string Gh, tnl::Vector3 Pos, int ActSpeed, int MaxIndex, int XNum, int YNum, int XSize, int YSize)
{
	//�A�j���[�V�����C���X�^���X����
	auto anim = std::make_shared<Animation>(Gh, Pos, ActSpeed, MaxIndex, XNum, YNum, XSize, YSize);
	//�A�j���[�V�������X�g�ɓo�^
	liveAnimationList.emplace_back(anim);
}

void InGameScene::UpdateAnimation()
{
	for (auto anim : liveAnimationList) {
		anim->Update();
	}
	DeleteAnimation();
}

void InGameScene::DrawAnimation()
{
	for (auto anim : liveAnimationList) {
		anim->Draw();
	}
}

void InGameScene::DeleteAnimation()
{
	auto itr = liveAnimationList.begin();
	while (itr != liveAnimationList.end()) {
		if (!(*itr)->GetIsAlive()) {
			itr = liveAnimationList.erase(itr);
			continue;
		}
		++itr;
	}
}

std::shared_ptr<Enemy> InGameScene::GetNearestEnemy()
{
	//��ԋ߂��G
	std::shared_ptr<Enemy> nearEnemy = nullptr;
	for (auto enemy : eManager->GetList()) {
		float minLength = 0;
		if (nearEnemy == nullptr) {
			nearEnemy = enemy;
			minLength = gManager->GetLength(player->GetPos(), enemy->GetPos());
			continue;
		}
		//player�Ƃ̋����ƃ`�F�b�N
		float distance = gManager->GetLength(player->GetPos(), enemy->GetPos());
		//minlength���Z�������炱����������
		if (minLength > distance) {
			nearEnemy = enemy;
			minLength = distance;
		}
	}
	return nearEnemy;
	/*player->SetMyTarget(nearEnemy);*/
}


