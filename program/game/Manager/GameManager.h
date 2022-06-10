//ゲーム全体を管理するマネージャクラス
//シングルトンで作られている
#pragma once
#include<vector>
#include<list>
#include<string>
#include<unordered_map>
#include"../../dxlib_ext/dxlib_ext.h"
#include<memory>

class SceneManager;
class FadeControl;
class Sound;
class Object;
class BulletManager;
class PartsManager;
class ModManager;
class Player;
class Factory;
class ObjectFactory;
class Observer;

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

	//ステージのリスト
	enum class STAGE :uint32_t {
		SOL,	//ステージ1 難易度低 
		AIGIS,	//ステージ2 難易度中 
		ICALOS,	//ステージ3 難易度低高
		MAX
	};

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

	//複数枚の連なった画像をvectorに格納する関数
	void LoadDivGraphEx(const std::string Gh, const int AllNum, const int WidthNum, const int HeightNum,
		int XSize, int YSize, std::vector<int>& GhVector);

	//DrawRotaGraphの短縮版
	void DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag);

	//Objectリストの初期化
	inline void ResetObjectList() {
		objects.clear();
	}
	//Objectリストへの追加
	inline void AddObjectList(std::shared_ptr<Object> Ptr) {
		objects.emplace_back(Ptr);
	}
	//objectリスト取得
	inline std::list<std::shared_ptr<Object>>& GetObjectList() {
		return objects;
	}
	//プレイヤーの取得
	inline std::shared_ptr<Player>& GetPlayer() {
		return player;
	}
	//プレイヤーの設定
	inline void	SetPlayer(std::shared_ptr<Player> Player) {
		player = Player;
	}

	//単位ベクトル取得関数
	inline tnl::Vector3 GetFixVector(float X, float Y) {

		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);

	}
	//引数のPos同士の距離を取得する関数
	inline float GetLength(tnl::Vector3 PosA, tnl::Vector3 PosB) {
		return std::sqrt(((PosA.x - PosB.x) * (PosA.x - PosB.x)) + ((PosA.y - PosB.y) * (PosA.y - PosB.y)));
	}
	//２つのベクトルの外積を求める関数 VecA:速度ベクトル VecB:方向ベクトル
	float GetCross(tnl::Vector3 VecA, tnl::Vector3 VecB);


	//オブジェクトリストからの排除
	void RemoveObjectList();

	int GetRandEx(int a, int b);

	const tnl::Vector3 SPAWNPOS = { 0,-50,0 };
	//画面内のランダムなポジションを取得する関数
	tnl::Vector3 GetRandomPos();

	//メルセンヌ・ツイスターを採用した正規分布ランダム関数
	int GerRandomNumInWeight(const std::vector<int>WeightList);


	//ステージ設定関数
	void SetMyStage(STAGE stage) {
		mystage = stage;
	}

	//選択したステージの長さを渡す関数
	inline const float GetStageLength() {
		return STAGELENGTH[static_cast<int>(mystage)];
	}

	//四角形のマウスクリック感知
	bool isClickedRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom);

	//四角形のマウス範囲内感知
	bool OnMouseRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom);


	//マウス座標
	int mousePosX = 0;
	int mousePosY = 0;

	//マウススクロール
	int mouseWheel = 0;

	//UIを並べる方向
	enum class DIR {
		HORIZONTAL,
		VERTICAL,
		MAX
	};

	//ModManager生成
	void CreateModManager();

	//Observer取得

	inline Observer* GetObserver() {
		return enemyChecker;
	}

	//パーツマネージャ読み込み終了フラグ取得
	inline bool GetLoadedFlag() {
		return isLoaded;
	}
	//パーツマネージャ読み込み終了フラグセット
	inline void SetLoadedFlag(){
		isLoaded = true;
	}

	//playerを作る関数
	std::shared_ptr<Player> CreatePlayer();

private:
	//シングルトンインスタンス
	static GameManager* instance;

	//BulletManagerインスタンス
	BulletManager* bManager = nullptr;

	//PartsManagerインスタンス
	PartsManager* pManager = nullptr;

	//パーツマネージャ読み込みフラグ
	bool isLoaded = false;

	//ModManagerインスタンス
	ModManager* mManager = nullptr;

	
	
	//オブザーバインスタンス
	Observer* enemyChecker = nullptr;

	//選択したステージ
	STAGE mystage = STAGE::SOL;
	//ステージの長さ
	const float STAGELENGTH[static_cast<uint32_t>(STAGE::MAX)] = { 1000,1500,2000 };

	//オブジェクトリスト
	std::list<std::shared_ptr<Object>> objects;

	//playerポインタ
	std::shared_ptr<Player>player = nullptr;

	//アイテム情報をexcelから読み取る関数
	void loadItem();

	std::vector<std::vector<std::string>> loadItemCsv;
};