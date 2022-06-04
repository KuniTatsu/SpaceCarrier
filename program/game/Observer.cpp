#include "Observer.h"
#include"Object/Enemy.h"
#include"Object/Player.h"
#include"Manager/GameManager.h"
#include"Manager/EnemyManager.h"

Observer::Observer()
{
	gManager = GameManager::Instance();
	player = gManager->GetPlayer();
}

Observer::~Observer()
{
}
//enemy���������ꂽ��Ă΂��֐�
void Observer::Update(std::shared_ptr<Enemy> enemy)
{
	//haveTarget==true:�^�[�Q�b�g�������Ă���Ȃ�㏑�����Ȃ�
	if (player->haveTarget()) {
		return;
	}
	//�������ꂽ�G�l�~�[��player�̃^�[�Q�b�g�֐��ɂԂ�����
	player->SetMyTarget(enemy);
}

void Observer::DebugPlayer()
{
	if (player == nullptr) {
		DrawStringEx(600, 200, -1, "Player���ݒ肳��Ă��܂���");
	}
	else
	{
		DrawStringEx(600, 200, -1, "Player��������܂���");
	}
}
