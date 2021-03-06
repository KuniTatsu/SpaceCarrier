#include "Player.h"
#include"../Manager/GameManager.h"
#include"Bullet.h"
#include"../Inventory.h"
#include"../Factory.h"
#include"../Ship.h"
#include"../ShipParts/PartsBase.h"
#include"../Manager/PartsManager.h"

Player::Player()
{
	Init();
	tnl::DebugTrace("\nPlayerが作成されました\n");

}

Player::~Player()
{
}

void Player::Update()
{
	//移動
	Move();
	//武器のクールダウン更新
	myShip->AllWeaponCoolDawnUpdate();
	////弾発射タイマー更新
	//shootTimer += gManager->deltatime;

	//missileTimer += gManager->deltatime;
}

void Player::Draw()
{
	gManager->DrawRotaGraphNormal(pos.x, pos.y, gh, true);
	if (autoTargetMode) {
		DrawStringEx(200, 200, -1, "オートターゲットON");
		//ターゲットサークル描画
		if (myTarget == nullptr)return;
		DrawRotaGraph(myTarget->GetPos().x, myTarget->GetPos().y, 1, 0, targetingCircle, true);
	}
	else DrawStringEx(200, 200, -1, "オートターゲットOFF");

	//全武器のクールダウン表示
	DrawWeaponCoolDown();
}

void Player::Init()
{
	pos = gManager->Center;
	gh = gManager->LoadGraphEx("graphics/Player_2525.png");

	targetingCircle = gManager->LoadGraphEx("graphics/TargetPointa.png");

	pManager = PartsManager::Instance();

	//playerの当たり判定半径
	radius = 12.5;

	//最大化重量のデフォルト
	maxCapacity = 500;

	//ステージ内を移動するスピード
	CruizeSpeed = 10;
	fac = gManager->GetFactory();
}

void Player::CheckIsLive()
{
}

bool Player::InventoryUpdate(std::shared_ptr<ShipParts>& Parts)
{
	//インベントリの上下移動
	partsInventory->InventoryMove();
	//パーツのアイコン画像をクリックしたらそのパーツのポインタを得る
	auto parts = partsInventory->InventorySelect();
	if (nullptr != parts) {
		//引数の参照にパーツポインタを渡す
		Parts = parts;
		return true;
	}
	return false;
}

void Player::DrawInventory()
{		//380x465
	partsInventory->InventoryDraw(partsInventory->guideX - 95, 30, partsInventory->guideX + 290, 495);
	//partsInventory->InventoryDraw(0, 30,1024, 495);
}

void Player::DrawShip()
{
	myShip->DrawShipParts();
}

void Player::ChangeShipParts(int PartsType, std::shared_ptr<ShipParts> NewParts)
{
	myShip->ChangeShipParts(PartsType, NewParts);
}

void Player::CreateNewParts()
{
	auto weight = pManager->GetDropWeight();

	auto id = gManager->GerRandomNumInWeight(weight);

	partsInventory->AddInventory(id);

}

void Player::Move()
{
	/*
	for (int i = 0; i < static_cast<int>(DIR::MAX); ++i) {
		if (tnl::Input::IsKeyDown(arrowKeys[i])) {

		}
	}
	*/
	//移動量リセット
	moveX = 0;
	moveY = 0;

	//どうにかしてまとめたい　関数化したいがうまく思いつかない
	//上下キー感知
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::UP)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::UP)];
		DrawStringEx(200, 300, -1, "UP");
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::DOWN)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::DOWN)];
	}

	//左右キー感知
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::RIGHT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::RIGHT)];
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::LEFT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::LEFT)];
		DrawStringEx(200, 400, -1, "LEFT");
	}

	//移動量が0でなければベクトルを正規化して移動させる
	if (moveX != 0 || moveY != 0) {

		tnl::Vector3 fixVec = gManager->GetFixVector(moveX, moveY);

		float fixMoveX = fixVec.x * SPEED;
		float fixMoveY = fixVec.y * SPEED;

		pos.x += fixMoveX;
		pos.y += fixMoveY;

		//もし画面端にいるなら移動しない
		if (pos.x < radius || pos.x>1024 - radius ||
			pos.y < radius || pos.y>768 - radius) {
			pos.x -= fixMoveX;
			pos.y -= fixMoveY;
		}

	}
}

void Player::DrawWeaponCoolDown()
{
	for (int i = 0; i < myShip->GetWeaponNum(); ++i) {
		auto coolDawn = myShip->GetCoolDown(i);
		DrawStringEx(200 + i * 30, 600, -1, "%0.0f", coolDawn);
	}
}

void Player::ShipInit()
{
	//パーツを入れるインベントリを生成
	partsInventory = std::make_shared<Inventory>();

	//初期パーツをインベントリに追加
	partsInventory->AddInventory(100);
	partsInventory->AddInventory(102);
	partsInventory->AddInventory(104);
	partsInventory->AddInventory(106);
	partsInventory->AddInventory(109);

	partsInventory->AddWeaponInventory(200);
	partsInventory->AddWeaponInventory(205);

	//船を生成
	myShip = std::make_shared<Ship>();

	//船のパーツリストの取得
	auto list = partsInventory->GetPartsInventory();
	//船の初期パーツの登録
	for (auto parts : list) {
		myShip->SetProtoParts(parts);
	}
	//船のステータス合計を計算
	myShip->SetShipStatus();

	//------debug------
	partsInventory->AddInventory(102);
	partsInventory->AddInventory(102);

	//-----------------

	//船の初期武器の登録
	auto weaponList = partsInventory->GetWeaponInventory();
	for (auto weapon : weaponList) {
		myShip->SetProtoWeapon(weapon);
	}
}

void Player::ShootBullet()
{
	myShip->ShootShipWeapon();
	/*
	//クールダウン中なら発射しない
	if (shootTimer < SHOOTCOOLDOWN)return;
	//クールダウンセット
	shootTimer = 0;

	//速度ベクトルセット
	tnl::Vector3 vec = { 0,-10,0 };

	tnl::DebugTrace("\n%d,%d,%d\n", pos.x, pos.y, pos.z);

	auto initPos = tnl::Vector3(0, -INITPOSY, 0);

	auto shootPoint = pos + initPos;


	//弾の生成
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vec, Factory::MOVETYPE::STRAIGHT));
	bullet->SetList();
	bullet->SetBulletList();
	*/

}
void Player::SetMyTarget(std::shared_ptr<Object> Target)
{
	myTarget = Target;
}


/*
//Playerに設定されたターゲットに向かって撃つオートターゲット射撃関数
void Player::AimShootBullet()
{
	//MyTargetが設定されているか確認
	if (!isSetTarget()) {
		tnl::DebugTrace("\nMyTargetが設定されていません\n");
		return;
	}

	//クールダウン中なら発射しない
	if (shootTimer < SHOOTCOOLDOWN)return;
	//クールダウンセット
	shootTimer = 0;

	auto initPos = tnl::Vector3(0, -INITPOSY, 0);

	auto shootPoint = pos + initPos;

	//TargetPos方向の方向ベクトルを取得する 正規化していないことに注意
	tnl::Vector3 pVec = myTarget->GetPos() - pos;


	////Targetの方向ベクトル成分を少し足す
	//tnl::Vector3 enemyVecSpeed = myTarget->GetVecSpeed() * gManager->deltatime;
	////逆方向なのでマイナスを掛ける
	//pVec += (enemyVecSpeed * -1);


	//弾の生成
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, pVec, Factory::MOVETYPE::TOENEMY));
	bullet->SetList();
	bullet->SetBulletList();

}
//直接目的のオブジェクトを引数にいれて呼び出すオートターゲット射撃関数
void Player::AimShootBullet(std::shared_ptr<Object> Target)
{
	//クールダウン中なら発射しない
	if (shootTimer < SHOOTCOOLDOWN)return;
	//クールダウンセット
	shootTimer = 0;

	tnl::DebugTrace("\n%d,%d,%d\n", pos.x, pos.y, pos.z);

	auto initPos = tnl::Vector3(0, -INITPOSY, 0);

	auto shootPoint = pos + initPos;

	//TargetPos方向の方向ベクトルを取得する 正規化していないことに注意
	tnl::Vector3 pVec = Target->GetPos() - pos;

	//弾の生成
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, pVec, Factory::MOVETYPE::TOENEMY));
	bullet->SetList();
	bullet->SetBulletList();
}

void Player::ShootMissile()
{
	//MyTargetが設定されているか確認
	if (!isSetTarget()) {
		tnl::DebugTrace("\nMyTargetが設定されていません\n");
		return;
	}
	//クールダウン中なら発射しない
	if (missileTimer < MISSILECOOLDOWN)return;
	//クールダウンセット
	missileTimer = 0;

	auto initPos = tnl::Vector3(0, -INITPOSY, 0);

	auto shootPoint = pos + initPos;

	tnl::Vector3 vPos = tnl::Vector3(0, -8.0f, 0);

	//弾の生成
	auto bullet = std::dynamic_pointer_cast<Bullet, Object>(fac->create("Bullet", shootPoint, vPos, Factory::MOVETYPE::TRACKING));
	bullet->SetList();
	bullet->SetBulletList();
}
*/