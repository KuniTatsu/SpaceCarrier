#include "GameManager.h"
#include"SceneManager.h"
#include"DxLib.h"
#include<string>
#include"../Object/Player.h"
#include"../Object/Bullet.h"
#include"../Object/Object.h"
#include"../Object/Enemy.h"
#include"../Manager/BulletManager.h"
#include"../Manager/PartsManager.h"
#include"../Manager/ModManager.h"
#include"../Object/Player.h"
#include"../Factory.h"
#include"../Observer.h"
#include<time.h>
#include<random>

//#include"Item.h"
//#include "FadeControl.h"
//#include "SoundManager.h"



GameManager::GameManager()
{
	//tnl::DebugTrace("\n�R���X�g���N�^���Ă΂ꂽ��\n");
}

GameManager* GameManager::Instance()
{
	if (instance == nullptr) {
		instance = new GameManager();
	}
	return instance;
}

GameManager::~GameManager()
{
	delete objFac;
	delete enemyChecker;
}

void GameManager::Update(const float Deltatime)
{
	deltatime = Deltatime;
	//�}�E�X���W�擾
	GetMousePoint(&mousePosX, &mousePosY);

	//�}�E�X�X�N���[���ʎ擾
	mouseWheel = GetMouseWheelRotVol();  //�z�C�[���̉�]�ʎ擾

	SceneManager::Update();
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_2))
	{
		auto hoge = std::make_shared<Bullet>();
		hoge->SetList();
	}



	/*auto it = objects.begin();
	while (it != objects.end()) {
		(*it)->Update();
		it++;
	}*/
}
void GameManager::Draw(const float Deltatime)
{
	SceneManager::Render();
	/*auto itr = objects.begin();
	for (int i = 0; i < objects.size(); ++i) {
		(*itr)->Draw();
	}*/
}

void GameManager::initGameManager()
{
	//sound = new Sound();
	//fControl = new FadeControl();

	deltatime = 0.0f;
	SRand(time(0));

	SceneManager::ChangeScene(SceneManager::SCENE::TITLE);
	testGraphic = LoadGraphEx("graphics/test_1.png");

	objFac = new ObjectFactory();

	////�v���C���[�̐���
	//player = std::make_shared<Player>();
	//player->SetList();

	//BulletManager�C���X�^���X�m��
	bManager = BulletManager::Instance();
	pManager = PartsManager::Instance();

	//�}�X�^�[�ǂݍ��݃t���O�X�V
	SetLoadedFlag();

	enemyChecker = new Observer();

}

int GameManager::LoadGraphEx(std::string Gh)
{

	auto it = ghmap.find(Gh);
	if (it != ghmap.end()) {
		return ghmap[Gh];
	}

	else {
		int loadgh = LoadGraph(Gh.c_str());
		ghmap.insert(std::make_pair(Gh, loadgh));
	}


	return ghmap[Gh];
}

void GameManager::LoadDivGraphEx(const std::string Gh, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize, std::vector<int>& GhVector)
{
	int* buf = new int[AllNum];
	LoadDivGraph(Gh.c_str(), AllNum, WidthNum, HeightNum, XSize, YSize, buf);


	for (int i = 0; i < AllNum; ++i) {
		GhVector.emplace_back(buf[i]);
	}
	delete[] buf;

}

void GameManager::DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag)
{
	DrawRotaGraph(X, Y, 1, 0, GrHandle, true);
}

float GameManager::GetCross(tnl::Vector3 VecA, tnl::Vector3 VecB)
{
	return (VecA.x * VecB.y) - (VecA.y * VecB.x);
}

void GameManager::RemoveObjectList()
{
	if (objects.size() <= 1)return;
	auto itr = objects.begin();

	while (itr != objects.end()) {
		if (!(*itr)->GetIsLive()) {
			itr = objects.erase(itr);
			continue;
		}
		itr++;
	}
}

//a����b�܂ł̒l���烉���_���Ɏ擾����
int GameManager::GetRandEx(int a, int b)
{
	if (a > b) {
		int diff = static_cast<int>(a - b);
		int random = static_cast<int>(GetRand(diff) + b);

		return random;
	}
	else {
		int diff = static_cast<int>(b - a);
		int random = static_cast<int>(GetRand(diff) + a);

		return random;
	}
	return 0;
}

tnl::Vector3 GameManager::GetRandomPos()
{
	float x = 0;
	x = static_cast<float>(GetRandEx(200, 900));

	return tnl::Vector3(x, SPAWNPOS.y, 0);
}

int GameManager::GerRandomNumInWeight(const std::vector<int> WeightList)
{
	// �񌈒�I�ȗ���������->�����V�[�h�Ɏg��
	std::random_device rnd;
	//�����_���Ȑ������߂邽�߂̊֐��������߂�
	//�����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
	std::mt19937 GetRandom(rnd());

	//���A���e�B�����肷��
	int totalWeight = 0;
	int selected = 0;

	//totalWeight�����߂�
	for (int i = 0; i < WeightList.size(); ++i) {
		totalWeight += WeightList[i];
	}
	//���͈͂̈�l���z�����擾
	std::uniform_int_distribution<> Weight(0, totalWeight);
	//���A���e�B�������_���Ō��߂�
	int rand = Weight(GetRandom);

	//--------��������E�F�C�g��p�������I--------//
	//���I
	for (int i = 0; i < WeightList.size(); i++) {
		if (rand < WeightList[i]) {
			//����
			selected = i;
			break;
		}

		// ���̑Ώۂ𒲂ׂ�
		rand -= WeightList[i];
	}
	return selected;
}

bool GameManager::isClickedRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	//�}�E�X�̍��W���l�p�`�̊O���Ȃ�return false
	if (MouseX<RectLeft || MouseX>RectRight || mousePosY<RectTop || mousePosY>RectBottom)return false;

	//�l�p�`�̓��������N���b�N���Ă�����
	if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
		return true;
	}
	return false;
}

bool GameManager::OnMouseRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	//�}�E�X�̍��W���l�p�`�̊O���Ȃ�return false
	if (MouseX<RectLeft || MouseX>RectRight || mousePosY<RectTop || mousePosY>RectBottom)return false;

	return true;
}

void GameManager::CreateModManager()
{
	mManager = ModManager::Instance();
}


std::shared_ptr<Player> GameManager::CreatePlayer()
{
	if (player != nullptr) {
		return player;
	}
	//�C���X�^���X����
	player = std::make_shared<Player>();
	//�D�𐶐�
	player->ShipInit();

	//Observer��player��o�^
	enemyChecker->SetPlayer(player);

	return player;

}


