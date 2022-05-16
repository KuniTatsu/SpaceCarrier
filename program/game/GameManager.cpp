#include "GameManager.h"
#include"SceneManager.h"
#include"DxLib.h"
#include<string>
#include"Object/Player.h"
#include"Object/Bullet.h"
#include"Manager/BulletManager.h"
#include"Object/Player.h"
#include"Factory.h"
#include<time.h>

//#include"Item.h"
//#include "FadeControl.h"
//#include "SoundManager.h"



GameManager::GameManager()
{
	tnl::DebugTrace("\nコンストラクタが呼ばれたよ\n");
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

}

void GameManager::Update(const float Deltatime)
{
	deltatime = Deltatime;

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

	SceneManager::ChangeScene(SceneManager::SCENE::TITLE);
	testGraphic = LoadGraphEx("graphics/test_1.png");

	objFac = new ObjectFactory();

	//プレイヤーの生成
	player = std::make_shared<Player>();
	player->SetList();

	//BulletManagerインスタンス確保
	bManager = BulletManager::Instance();

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

void GameManager::DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag)
{
	DrawRotaGraph(X, Y, 1, 0, GrHandle, true);
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

//aからbまでの値からランダムに取得する
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
	x = static_cast<float>(GetRandEx(200, 1000));

	return tnl::Vector3(x, SPAWNPOS.y, 0);
}



void GameManager::loadItem()
{
	loadItemCsv = tnl::LoadCsv("Csv/Item.csv");
	for (int i = 1; i < loadItemCsv.size(); ++i) {

		//id
		int a = std::atoi(loadItemCsv[i][0].c_str());
		//ItemType
		int b = std::atoi(loadItemCsv[i][1].c_str());
		//setDay
		int c = std::atoi(loadItemCsv[i][2].c_str());
		//addStatus
		int d = std::atoi(loadItemCsv[i][3].c_str());
		//addStatusNum
		int e = std::atoi(loadItemCsv[i][4].c_str());
		//setAbility
		int f = std::atoi(loadItemCsv[i][5].c_str());
		//setAbilityType
		int g = std::atoi(loadItemCsv[i][6].c_str());
		//num
		int h = std::atoi(loadItemCsv[i][10].c_str());


		//Item* abi = new Item(a, b, c, d, e, f, g, loadItemCsv[i][7], loadItemCsv[i][8], loadItemCsv[i][9], h);

		//abilitytypeごとにリストに格納
		//itemList[b].emplace_back(abi);
	}
}

