#include "Factory.h"
#include"Object/Object.h"
#include"Object/Bullet.h"
#include"Object/Enemy.h"
#include"Object/Player.h"
#include"EnemyData.h"
#include"StrategyPattern/MovementPattern.h"
#include"StrategyPattern/ShootPattern.h"
#include"Manager/GameManager.h"
#include"Manager/EnemyManager.h"


ObjectFactory::ObjectFactory()
{
	//tnl::DebugTrace("\nFactory子クラスが生成されました。\n");
}

//弾を作る関数
std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	if (type == "Bullet") {
		//移動方法によって生成を変える
		if (Move == MOVETYPE::STRAIGHT) {
			MovementBase* move = new StraightMove(VPos);
			return std::make_shared<Bullet>(StartPos, move);
		}
		//問題点:弾がプレイヤーのいた座標に向かって飛んでいくのはいいが、その場所でずっととどまり続ける地雷になってしまう
		//CenterStopMoveではなく、プレイヤーとStartPosの方向ベクトルを取り、正規化,VPosの大きさをかけてStraightで飛ばすほうが良さそう
		else if (Move == MOVETYPE::STOPPOS) {
			float speed = VPos.y;
			//MovementBase* move = new CenterStopMove(speed,)
			std::shared_ptr<Player>player = gManager->GetPlayer();
			tnl::Vector3 vec = player->GetPos() - StartPos;
			tnl::Vector3 fixVec = gManager->GetFixVector(vec.x, vec.y);

			MovementBase* move = new StraightMove(fixVec * speed);
			return std::make_shared<Bullet>(StartPos, move);
		}
		else if (Move == MOVETYPE::ACCEL) {

			MovementBase* move = new AccelMove(VPos);
			return std::make_shared<Bullet>(StartPos, move);
		}
		else if (Move == MOVETYPE::TOENEMY) {
			//VPosを正規化する
			tnl::Vector3 fixVec = gManager->GetFixVector(VPos.x, VPos.y);
			//速度 いずれどっかから持ってくる
			float speed = 5.0f;
			//moveを生成
			MovementBase* move = new StraightMove(fixVec * speed);
			return std::make_shared<Bullet>(StartPos, move);
		}
		else if (Move == MOVETYPE::TRACKING) {
			std::shared_ptr<Player>player = gManager->GetPlayer();
			//playerの持っているターゲットの情報を取得
			auto target = player->GetMyTarget();
			//動き方を生成
			MovementBase* track = new ToTargetMove(VPos, target);

			return std::make_shared<Bullet>(StartPos, track);
		}
		return std::shared_ptr<Object>();
	}
}
//敵を作る関数
std::shared_ptr<Object>ObjectFactory::CreateObject(const tnl::Vector3& StartPos, const tnl::Vector3& VPos, std::shared_ptr<EnemyData>Data) {

	//敵のステータス取得
	float* status = Data->GetStatus();
	//敵画像のパス取得
	std::string pass = Data->GetGhPass();
	//動き方
	MovementBase* move = nullptr;
	//撃ち方
	ShootBase* shoot = nullptr;
	//特殊な撃ち方
	ShootBase* exShoot = nullptr;

	//-------------------移動方法決定-------------------//
	//移動方法によって生成を変える
	if (Data->GetMoveType() == MOVETYPE::STRAIGHT) {
		move = new StraightMove(VPos);
	}
	else if (Data->GetMoveType() == MOVETYPE::FARSTOP) {
		move = new FarStopMove(VPos, 100);
	}
	else if (Data->GetMoveType() == MOVETYPE::MIDDLESTOP) {
		move = new FarStopMove(VPos, gManager->Center.y);
	}
	else if (Data->GetMoveType() == MOVETYPE::STOPPOS) {
		move = new CenterStopMove(2.0f, gManager->Center);
	}
	else if (Data->GetMoveType() == MOVETYPE::SLIDE) {
		
		move = new SlideMove(VPos);
	}
	else if (Data->GetMoveType() == MOVETYPE::ACCEL) {
		move = new AccelMove(VPos);
	}

	//-------------------射撃方法決定-------------------//
	//弾の発射方法によって生成を変える
	//直線射撃なら
	if (Data->GetShootType() == SHOOTTYPE::STRAIGHT) {

		//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
		tnl::Vector3 vecSpeed = { 0,10,0 };
		float coolDawn = 0.5f;

		shoot = new StraightShoot(vecSpeed, coolDawn);
	}
	//精密射撃なら
	else if (Data->GetShootType() == SHOOTTYPE::FOCUS) {
		//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
		tnl::Vector3 vecSpeed = { 0,10,0 };
		float coolDawn = 0.5f;
		shoot = new FocusShoot(vecSpeed, coolDawn);
	}
	//加速射撃なら
	else if (Data->GetShootType() == SHOOTTYPE::FAST) {
		//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
		tnl::Vector3 vecSpeed = { 0,8,0 };
		float coolDawn = 0.25f;
		shoot = new FastShoot(vecSpeed, coolDawn);
	}

	//-------------------特殊射撃方法決定-------------------//
	//特殊射撃がSTRAIGHTなら
	if (Data->GetExShootType() == SHOOTTYPE::STRAIGHT) {
		//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
		tnl::Vector3 vecSpeed = { 0,15,0 };
		float coolDawn = 0.5f;

		exShoot = new StraightShoot(vecSpeed, coolDawn);
	}
	//特殊射撃がFOCUSなら
	else if (Data->GetExShootType() == SHOOTTYPE::FOCUS) {
		//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
		tnl::Vector3 vecSpeed = { 0,10,0 };
		float coolDawn = 0.5f;

		exShoot = new FocusShoot(vecSpeed, coolDawn);
	}
	//特殊射撃がFASTなら
	else if (Data->GetExShootType() == SHOOTTYPE::FAST) {
		//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
		tnl::Vector3 vecSpeed = { 0,8,0 };
		float coolDawn = 0.25f;

		exShoot = new StraightShoot(vecSpeed, coolDawn);
	}


	//-------------enemyを作る------------------
	//もし特殊射撃を持つなら
	if (exShoot != nullptr) {
		return std::make_shared<Enemy>(StartPos, pass, status[0], status[1], status[2], status[3], move, shoot, exShoot);
	}
	else
	{
		return std::make_shared<Enemy>(StartPos, pass, status[0], status[1], status[2], status[3], move, shoot);
	}

}

//memo レーザー作る時に使う->tnl::IsIntersectRayOBB


Factory::Factory()
{
	//tnl::DebugTrace("\nFactory親クラスが生成されました。\n");
	gManager = GameManager::Instance();
}

//--------------------------Object型を生成する関数------------------------------------//

std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	auto object = CreateObject(type, StartPos, VPos, Move);

	return object;
}
//敵を作るcreate関数
std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, ENEMYTYPE EnemyType)
{
	auto data = GetEnemyData(static_cast<int>(EnemyType));

	auto object = CreateObject(StartPos, VPos, data);

	return object;
}

void Factory::GetEnemyManager()
{
	eManager = EnemyManager::Instance();
}


std::shared_ptr<EnemyData> Factory::GetEnemyData(int EnemyType)
{
	return eManager->GetRandomEnemyData(EnemyType);
}



//------------------------------------------------------------------------------------//

