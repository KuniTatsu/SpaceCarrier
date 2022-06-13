//船を改造したり荷物を積載したりするシーン

#pragma once
#include"Scene.h"
#include"../Manager/GameManager.h"
#include<memory>
#include<vector>
#include<functional>
#include<string>

class Player;
class Ship;
class ShipParts;
class Menu;
class SelectMenu;

class CustomizeScene :public BaseScene
{
public:
	CustomizeScene();
	~CustomizeScene();

	void Update();
	void Draw();

private:

	//--------------ポインタ関係----------------------//
	// 
	//playerのインスタンス
	std::shared_ptr<Player>player = nullptr;
	//GameManagerのインスタンス
	GameManager* gManager = nullptr;

	//パーツ装備メニューのインスタンス
	std::shared_ptr<SelectMenu>partsEquipMenu = nullptr;

	//ステータスの背景UI
	std::shared_ptr<Menu>equipBack = nullptr;
	std::shared_ptr<Menu>statusBack = nullptr;

	std::shared_ptr<Menu>uiBack = nullptr;
	//uiBackMenuの左上座標
	tnl::Vector3 topPos;

	//shipのインスタンス
	std::shared_ptr<Ship>playerShip = nullptr;

	//インベントリでクリックしたときにパーツを指定した際の入れ物
	std::shared_ptr<ShipParts> selectedParts = nullptr;

	//------------------------------------------------//

	//初期化関数
	void Init();

	//船に装備中のパーツ一覧を描画する関数
	void DrawEquipParts();

	//船のステータス一覧を描画する関数
	void DrawShipStatus(int TopX, int TopY);


	//警告画像フラグ
	bool isCaution = false;

	//船のパーツ名
	const std::string PARTSNAME[5] = { "船体","貨物室","装甲","発電機","スラスター" };

	const std::string STATUSNAME[5] = { "体力","電力","防御力","速度","貨物容量" };

	//--------------シークエンス関係----------------//
	tnl::Sequence<CustomizeScene>mainSeqence =
		tnl::Sequence<CustomizeScene>(this, &CustomizeScene::SeqTop);

	//カスタマイズシーンのトップページシークエンス
	bool SeqTop(const float deltatime);
	//選択シークエンス
	bool SeqSelect(const float deltatime);
	//船改造シークエンス
	bool SeqShipCustomize(const float deltatime);
	//武器選択シークエンス
	bool SeqWeaponCustomize(const float deltatime);



	//シークエンスの列挙体
	enum class sequence :uint32_t {
		TOP,
		SELECT,
		SHIPCUSTOM,
		WEAPONCUSTOM,
		MAX

	};
	//topメニューから飛ぶ際のメニュー番号
	sequence SEQ[2] = { sequence::SELECT,sequence::WEAPONCUSTOM };

	//今のシークエンス
	sequence nowSeq = sequence::TOP;
	//一つ前のシークエンス
	sequence lastSeq = sequence::TOP;

	//Sequenceを移動させる関数,enumも一緒に変更する
	void ChangeSequence(const sequence seq);


	//シークエンス毎の描画関数

	//トップシークエンスのみの描画
	void DrawTopSeq();
	//セレクトシークエンスのみの描画
	void DrawSelectSeq();
	//船カスタマイズシーンのみの描画
	void DrawCustomSeq();
	//武器カスタマイズシーンのみの描画
	void DrawWeaponSeq();

	//今のシークエンスでのみ描画したい関数を入れるファンクション
	std::function< void(CustomizeScene*) > drawFunc = &CustomizeScene::DrawTopSeq;


	//----------------------------------------------//

	//---------------画像ハンドル-------------------//

	std::vector<int>ghs = {};

	//---topシークエンスのmenu画像
	int menuShipCustomGh = 0;
	int menuWeaponCustomGh = 0;
	int menuReturnGh = 0;
	//---

	//topシークエンスのmenu画像サイズ
	const int GRAPHICSIZE = 240;

	//topシークエンスのmenu画像描画中心座標
	const tnl::Vector3 GRAPHICCENTER[3] = { tnl::Vector3(200,600,0),tnl::Vector3(520,600,0),tnl::Vector3(840,600,0) };

	//背景画像
	int background = 0;
	//menuハイライト画像
	int highright = 0;

	//装備中警告画像
	int caution = 0;


	//-----------------------------------------------//


};

