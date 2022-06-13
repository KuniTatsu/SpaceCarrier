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
	//tnl::DebugTrace("\nコンストラクタが呼ばれたよ\n");
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
	//マウス座標取得
	GetMousePoint(&mousePosX, &mousePosY);

	//マウススクロール量取得
	mouseWheel = GetMouseWheelRotVol();  //ホイールの回転量取得

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

	////プレイヤーの生成
	//player = std::make_shared<Player>();
	//player->SetList();

	//BulletManagerインスタンス確保
	bManager = BulletManager::Instance();
	pManager = PartsManager::Instance();

	//マスター読み込みフラグ更新
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
	x = static_cast<float>(GetRandEx(200, 900));

	return tnl::Vector3(x, SPAWNPOS.y, 0);
}

int GameManager::GerRandomNumInWeight(const std::vector<int> WeightList)
{
	// 非決定的な乱数生成器->初期シードに使う
	std::random_device rnd;
	//ランダムな数を求めるための関数名を決める
	//メルセンヌ・ツイスタの32ビット版、引数は初期シード
	std::mt19937 GetRandom(rnd());

	//レアリティを決定する
	int totalWeight = 0;
	int selected = 0;

	//totalWeightを求める
	for (int i = 0; i < WeightList.size(); ++i) {
		totalWeight += WeightList[i];
	}
	//一定範囲の一様分布乱数取得
	std::uniform_int_distribution<> Weight(0, totalWeight);
	//レアリティをランダムで決める
	int rand = Weight(GetRandom);

	//--------ここからウェイトを用いた抽選--------//
	//抽選
	for (int i = 0; i < WeightList.size(); i++) {
		if (rand < WeightList[i]) {
			//決定
			selected = i;
			break;
		}

		// 次の対象を調べる
		rand -= WeightList[i];
	}
	return selected;
}

bool GameManager::isClickedRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	//マウスの座標が四角形の外側ならreturn false
	if (MouseX<RectLeft || MouseX>RectRight || mousePosY<RectTop || mousePosY>RectBottom)return false;

	//四角形の内側かつ左クリックしていたら
	if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
		return true;
	}
	return false;
}

bool GameManager::OnMouseRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	//マウスの座標が四角形の外側ならreturn false
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
	//インスタンス生成
	player = std::make_shared<Player>();
	//船を生成
	player->ShipInit();

	//Observerにplayerを登録
	enemyChecker->SetPlayer(player);

	return player;

}


