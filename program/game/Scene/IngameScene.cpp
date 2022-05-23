#include "InGameScene.h"
#include"../Manager/BulletManager.h"
#include"../Manager/EnemyManager.h"
#include"../Object/Bullet.h"
#include"../Manager/GameManager.h"
#include"../Object/Object.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include"../Factory.h"
#include<time.h>
#include"../Animation.h"

InGameScene::InGameScene()
{
	Init();
}

InGameScene::~InGameScene()
{
}

void InGameScene::Update()
{
	//アニメーション更新
	UpdateAnimation();
	//現在のシークエンスのアップデート
	mainSeqence.update(gManager->deltatime);
}

void InGameScene::Draw()
{
	//一枚目の背景画像
	DrawRotaGraph(backGroundPos.x, backGroundPos.y, 2, 0, backGroundGh, false);
	DrawRotaGraph(backGroundPos.x, backGroundPos.y - SIZEY, 2, 0, testGh, false);

	auto objectList = gManager->GetObjectList();
	auto itr = objectList.begin();

	for (int i = 0; i < objectList.size(); ++i) {
		(*itr)->Draw();
		++itr;
	}
	//アニメーション描画
	DrawAnimation();
	//進捗ゲージ描画
	DrawProgressGauge();

	if (nowSeq == sequence::GOALRESALT) {
		gManager->DrawRotaGraphNormal(gManager->Center.x, gManager->Center.y, goalTestGh, false);
	}
}

void InGameScene::Init()
{
	gManager = GameManager::Instance();
	bManager = BulletManager::Instance();
	eManager = EnemyManager::Instance();

	backGroundGh = gManager->LoadGraphEx("graphics/space.jpg");
	testGh = gManager->LoadGraphEx("graphics/space.jpg");

	stageGaugeBase = gManager->LoadGraphEx("graphics/StageGauge_None.png");
	stageGaugeFill = gManager->LoadGraphEx("graphics/StageGauge_Fill.png");

	goalTestGh = gManager->LoadGraphEx("graphics/TestGoal.png");

	backGroundPos = { gManager->Center.x,gManager->Center.y,0 };

	//プレイヤーの生成
	player = std::make_shared<Player>();
	player->SetList();
	gManager->SetPlayer(player);

	//プレイヤーの巡航速度を取得
	PlayerSpeed = player->GetCruizeSpeed();
	//荷重率の取得
	CapacityRate = player->GetCapaciryRate();
	//オブジェクトファクトリーの取得
	fac = gManager->GetFactory();
	fac->GetEnemyManager();
	//ステージの長さの取得
	stageLength = gManager->GetStageLength();


}

bool InGameScene::SeqCruize(const float deltatime)
{
	//背景移動
	MoveBackGround();

	//ステージ進捗更新
	//もしゴールについたらtrueが帰る
	if (Cruize()) {
		//すべての敵と弾をリストから消去する
		//-----インスタンス消去-------
		bManager->ResetBulletList();
		bManager->ResetEnemyBulletList();
		eManager->ResetEnemyList();
		gManager->ResetObjectList();
		//----------------------------
		//リザルトシークエンスに飛ぶ
		ChangeSequence(sequence::GOALRESALT);
		return true;
	}

	//敵の生成　いずれEnemyManagerを介してマスターデータからEnemyの種類を決定,生成する eManager->CreateEnemy("NORMAL",startpos,vpos);
	if (GetRand(100) % 100 > 98) {
		/*auto enemy = std::dynamic_pointer_cast<Enemy, Object>(fac->create("Enemy", gManager->GetRandomPos(),
			tnl::Vector3(0, 2, 0), Factory::MOVETYPE::STOPPOS , Factory::SHOOTTYPE::STRAIGHT));*/

		auto enemy = eManager->CreateEnemy(EnemyManager::ENEMYTYPE::NORMAL, gManager->GetRandomPos(), tnl::Vector3(0, 2, 0));
		enemy->SetList();
		enemy->SetEnemyList();

	}

	//TABを押したら一番近くの敵をオートターゲットする
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_TAB)) {
		//playerから一番近い敵をオートターゲット目標として登録
		player->SetMyTarget(GetNearestEnemy());

		//オートターゲットの更新を有効にする
		player->ChageAutoTargerMode();
	}
	//ターゲットが設定されていればオートターゲット射撃が可能
	//spaceキーを押したら弾を発射する
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_SPACE)) {
		if (player->isAutoTargetMode()) {
			player->AimShootBullet();
		}
		player->ShootBullet();
	}

	//オブジェクトリストのアップデート
	{
		auto list = gManager->GetObjectList();
		auto it = list.begin();

		while (it != list.end()) {
			(*it)->Update();
			it++;
		}
	}
	//弾とエネミーの当たり判定
	for (auto enemy : eManager->GetList()) {
		for (auto bullet : bManager->GetList()) {
			if (tnl::IsIntersectSphere(enemy->GetPos(), enemy->GetRadius(), bullet->GetPos(), bullet->GetRadius())) {
				//アニメーションを生成する
				MakeAnimation("graphics/Explosion.png", enemy->GetPos(), 10, 7, 7, 1, 120, 120);
				//敵と弾を死亡状態にする
				enemy->SetIsLive();
				bullet->SetIsLive();
				isDestroyEnemy = true;
			}
		}
	}
	//インスタンス消去
	bManager->RemoveBulletList();
	eManager->RemoveEnemyList();
	gManager->RemoveObjectList();

	if (isDestroyEnemy) {

		isDestroyEnemy = false;
		//オートターゲットがONなら次のターゲットを登録する
		if (!player->isAutoTargetMode())return true;

		//ターゲットを消去
		player->CleanTarget();
		//playerから一番近い敵をオートターゲット目標として登録
		player->SetMyTarget(GetNearestEnemy());


	}

	return true;
}
//ゴールリザルト描画シークエンス
bool InGameScene::SeqGoalResalt(const float deltatime)
{
	//もしEnterを押したら最初からスタートする
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) {
		//ステージの進捗状況をリセットする
		ResetStageProgress();

		//プレイヤーの生成
		player = std::make_shared<Player>();
		player->SetList();

		ChangeSequence(sequence::CRUIZE);
		return true;
	}
	return true;
}
//シークエンスを変更する関数
void InGameScene::ChangeSequence(const sequence seq)
{
	//今のシークエンスと一つ前のシークエンスをそれぞれ更新
	lastSeq = nowSeq;
	nowSeq = seq;

	//シークエンスを切り替える
	switch (seq)
	{
	case sequence::CRUIZE: {
		mainSeqence.change(&InGameScene::SeqCruize);
		break;
	}
	case sequence::GOALRESALT: {
		mainSeqence.change(&InGameScene::SeqGoalResalt);
		break;
	}
	default:
		break;
	}
}
void InGameScene::MoveBackGround()
{
	backGroundPos.y += 5;
	//画面下端に画像の上端が移動したら
	if (backGroundPos.y - 480 >= 768) {
		//元に戻す 元画像サイズと画面サイズの差を引く
		backGroundPos.y = gManager->Center.y - 72;
	}
}

bool InGameScene::Cruize()
{
	//一秒で進む距離を取得 巡航速度と荷重率,レーン補正をかけた値を乗算
	//荷重率は逆数をかける(軽い(1未満)と早くなり、重い(1以上)と遅くなる)
	float addCruizeDistance = 0;
	//荷重率が0の場合は無視する
	if (CapacityRate == 0) {
		addCruizeDistance = (PlayerSpeed * LANEEXRATIO[static_cast<int>(myLane)]);
	}
	else {
		addCruizeDistance = (PlayerSpeed * LANEEXRATIO[static_cast<int>(myLane)]) / CapacityRate;
	}

	//progressが1になっていれば加算しない
	if (progress >= 1.0)return true;
	//現在地に加算する
	nowStayPos += addCruizeDistance * gManager->deltatime;

	//debug
	//nowStayPos += addCruizeDistance * gManager->deltatime * 10;

	//ステージの進捗率更新
	progress = static_cast<double>(nowStayPos / stageLength);
	//debug
	//tnl::DebugTrace("\n%.2f\n", progress);

	return false;
}

void InGameScene::DrawProgressGauge()
{
	//ステージ進行ゲージの描画
	DrawRotaGraph(1024 - 25, gManager->Center.y, 1, 0, stageGaugeBase, true);
	//現在の進行度に応じてゲージの長さを描画
	DrawRotaGraph3(1024, 768 - 5, 50, 768, 1, progress, 0, stageGaugeFill, true);
}

void InGameScene::ResetStageProgress()
{
	//初期位置にリセット
	nowStayPos = 0.0f;
	//進捗を0にリセット
	progress = 0.0f;
	//playerの描画座標を画面中心に移動
	player->SetPos(gManager->Center);
}

void InGameScene::MakeAnimation(std::string Gh, tnl::Vector3 Pos, int ActSpeed, int MaxIndex, int XNum, int YNum, int XSize, int YSize)
{
	//アニメーションインスタンス生成
	auto anim = std::make_shared<Animation>(Gh, Pos, ActSpeed, MaxIndex, XNum, YNum, XSize, YSize);
	//アニメーションリストに登録
	liveAnimationList.emplace_back(anim);
}

void InGameScene::UpdateAnimation()
{
	for (auto anim : liveAnimationList) {
		anim->Update();
	}
	DeleteAnimation();
}

void InGameScene::DrawAnimation()
{
	for (auto anim : liveAnimationList) {
		anim->Draw();
	}
}

void InGameScene::DeleteAnimation()
{
	auto itr = liveAnimationList.begin();
	while (itr != liveAnimationList.end()) {
		if (!(*itr)->GetIsAlive()) {
			itr = liveAnimationList.erase(itr);
			continue;
		}
		++itr;
	}
}

std::shared_ptr<Enemy> InGameScene::GetNearestEnemy()
{
	//一番近い敵
	std::shared_ptr<Enemy> nearEnemy = nullptr;
	for (auto enemy : eManager->GetList()) {
		float minLength = 0;
		if (nearEnemy == nullptr) {
			nearEnemy = enemy;
			minLength = gManager->GetLength(player->GetPos(), enemy->GetPos());
			continue;
		}
		//playerとの距離とチェック
		float distance = gManager->GetLength(player->GetPos(), enemy->GetPos());
		//minlengthより短かったらこっちを入れる
		if (minLength > distance) {
			nearEnemy = enemy;
			minLength = distance;
		}
	}
	return nearEnemy;
	/*player->SetMyTarget(nearEnemy);*/
}


