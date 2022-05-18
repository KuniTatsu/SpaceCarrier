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
class Factory;
class ObjectFactory;

class GameManager {

protected:
	GameManager();
	~GameManager();
public:
	//インスタンスがなければ生成、あれば返す関数
	static GameManager* Instance();

	//オブジェクトファクトリーインスタンス
	Factory* objFac = nullptr;
	//ファクトリーの取得

	inline Factory* GetFactory() {
		return objFac;
	}

	int testGraphic = 0;

	/*
	FadeControl* fControl = nullptr;
	Sound* sound = nullptr;*/

	//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;

	//フレーム秒
	float deltatime = 0.0f;

	//画面中央座標
	const tnl::Vector3 Center = { 512,384,0 };


	void Update(const float Deltatime);
	void Draw(const float Deltatime);

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

	int GetRandEx(int a, int b);

	const tnl::Vector3 SPAWNPOS = { 0,-50,0 };
	//画面内のランダムなポジションを取得する関数
	tnl::Vector3 GetRandomPos();

	//選択したステージの長さを渡す関数
	inline const float GetStageLength() {
		return STAGELENGTH[static_cast<int>(mystage)];
	}


private:
	//シングルトンインスタンス
	static GameManager* instance;

	//BulletManagerインスタンス
	BulletManager* bManager = nullptr;

	//ステージのリスト
	enum class STAGE:uint32_t {
		SOL,	//ステージ1 難易度低 
		AIGIS,	//ステージ2 難易度中 
		ICALOS,	//ステージ3 難易度低高
		MAX
	};
	
	//選択したステージ
	STAGE mystage = STAGE::SOL;
	//ステージの長さ
	const float STAGELENGTH[static_cast<uint32_t>(STAGE::MAX)] = {1000,1500,2000};

	//オブジェクトリスト
	std::list<std::shared_ptr<Object>> objects;

	std::shared_ptr<Player>player = nullptr;

	//アイテム情報をexcelから読み取る関数
	void loadItem();

	std::vector<std::vector<std::string>> loadItemCsv;
};