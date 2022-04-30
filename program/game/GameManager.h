//ゲーム全体を管理するマネージャクラス
//シングルトンで作られている


#pragma once
#include<vector>
#include<list>
#include<string>
#include<unordered_map>
#include"../dxlib_ext/dxlib_ext.h"
#include<memory>

class SceneManager;
class FadeControl;
class Sound;

class GameManager {

protected:
	GameManager();
	~GameManager();
public:
	//インスタンスがなければ生成、あれば返す関数
	static GameManager* Instance();
	//static std::shared_ptr<GameManager> Instance();


	int testGraphic = 0;

	/*SceneManager* sManager = nullptr;
	FadeControl* fControl = nullptr;
	Sound* sound = nullptr;*/



	//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;

	float deitatime_;


	void Update();
	void Draw();

	//GameManagerの初期化
	void initGameManager();

	//画像を読み込んでmapに入れる関数
	//すでにあるghならそれを返す
	int LoadGraphEx(std::string Gh);

	//DrawRotaGraphの短縮版
	void DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag);



private:
	//シングルトンインスタンス
	static GameManager* instance;
	//static std::shared_ptr<GameManager> instance;

	//プレイヤーキャラクタGh
	int playerGh[12] = {};


	//アイテム情報をexcelから読み取る関数
	void loadItem();

	std::vector<std::vector<std::string>> loadItemCsv;
};