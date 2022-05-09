#include "GameManager.h"
#include"SceneManager.h"
#include"DxLib.h"
#include<string>
#include"Object/Player.h"
#include"Object/Bullet.h"


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

void GameManager::Update()
{
	SceneManager::Update();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
		auto hoge=std::make_shared<Player>();
		hoge->SetList();
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_2))
	{
		auto hoge = std::make_shared<Bullet>();
		hoge->SetList();
	}

	auto itr = objects.begin();

	for (int i = 0; i < objects.size(); ++i) {
		(*itr)->Update();
	}

}
void GameManager::Draw()
{
	SceneManager::Render();
	auto itr = objects.begin();

	for (int i = 0; i < objects.size(); ++i) {
		(*itr)->Draw();
	}
}

void GameManager::initGameManager()
{
	
	//sound = new Sound();
	//fControl = new FadeControl();

	deitatime_ = 0;

	SceneManager::ChangeScene(SceneManager::SCENE::TITLE);
	testGraphic = LoadGraphEx("graphics/test_1.png");
	auto hoge = std::make_shared<Player>();
	hoge->SetList();
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

