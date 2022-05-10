//ゲーム全体を管理するマネージャクラス
//シングルトンで作られている
#pragma once
#include<vector>
#include<list>
#include<string>
#include<unordered_map>
#include"../dxlib_ext/dxlib_ext.h"
#include<memory>
#include"Object/Object.h"

class SceneManager;
class FadeControl;
class Sound;
class Object;
class BulletManager;
class Player;

class GameManager {

protected:
	GameManager();
	~GameManager();
public:
	//インスタンスがなければ生成、あれば返す関数
	static GameManager* Instance();


	int testGraphic = 0;

	/*
	FadeControl* fControl = nullptr;
	Sound* sound = nullptr;*/

	//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;

	float deitatime_ = 0;
	//画面中央座標
	const tnl::Vector3 Center = { 512,364,0 };


	void Update();
	void Draw();

	//GameManagerの初期化
	void initGameManager();

	//画像を読み込んでmapに入れる関数
	//すでにあるghならそれを返す
	int LoadGraphEx(std::string Gh);

	//DrawRotaGraphの短縮版
	void DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag);

	//Objectリストへの追加
	inline void AddObjectList(std::shared_ptr<Object> Ptr) {
		objects.emplace_back(Ptr);
	}
	//objectリスト取得
	inline std::list<std::shared_ptr<Object>>& GetObjectList() {
		return objects;
	}

	inline std::shared_ptr<Player> GetPlayer() {
		return player;
	}

	void RemoveObjectList();


private:
	//シングルトンインスタンス
	static GameManager* instance;

	//BulletManagerインスタンス
	BulletManager* bManager = nullptr;

	std::list<std::shared_ptr<Object>> objects;

	std::shared_ptr<Player>player = nullptr;

	//アイテム情報をexcelから読み取る関数
	void loadItem();

	std::vector<std::vector<std::string>> loadItemCsv;
};