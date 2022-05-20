#include "Factory.h"
#include"Object/Object.h"
#include"Object/Bullet.h"
#include"Object/Enemy.h"
#include"EnemyData.h"
#include"StrategyPattern/MovementPattern.h"
#include"StrategyPattern/ShootPattern.h"
#include"Manager/GameManager.h"
#include"Manager/EnemyManager.h"

ObjectFactory::ObjectFactory()
{
	tnl::DebugTrace("\nFactory子クラスが生成されました。\n");
}

std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot)
{
	if (type == "Enemy") {
		//移動方法によって生成を変える
		if (Move == MOVETYPE::STRAIGHT) {
			MovementBase* move = new StraightMove(VPos);

			//弾の発射方法によって生成を変える
			if (Shoot == SHOOTTYPE::STRAIGHT) {

				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* shoot = new StraightShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot);
			}
		}
		/*
		else if (Move == MOVETYPE::STOPPOS) {
			MovementBase* move = new CenterStopMove(2.0f, gManager->Center);
			//弾の発射方法によって生成を変える
			if (Shoot == SHOOTTYPE::STRAIGHT) {

				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* shoot = new StraightShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot);
			}
		}
		*/
	}
	else if (type == "Bullet") {
		//移動方法によって生成を変える
		if (Move == MOVETYPE::STRAIGHT) {
			MovementBase* move = new StraightMove(VPos);
			return std::make_shared<Bullet>(StartPos, move);
		}
	}

}

std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos, MOVETYPE Move)
{
	if (type == "Bullet") {
		//移動方法によって生成を変える
		if (Move == MOVETYPE::STRAIGHT) {
			MovementBase* move = new StraightMove(VPos);
			return std::make_shared<Bullet>(StartPos, move);
		}
		//問題点:弾がプレイヤーのいた座標に向かって飛んでいくのはいいが、その場所でずっととどまり続ける地雷になってしまう
		/*else if (Move == MOVETYPE::STOPPOS) {
			float speed = VPos.y;
			MovementBase* move = new CenterStopMove(speed,)
		}*/
		return std::shared_ptr<Object>();
	}
}

std::shared_ptr<Object>ObjectFactory::CreateObject(const tnl::Vector3& StartPos, const tnl::Vector3& VPos, std::shared_ptr<EnemyData>Data) {

	//移動方法によって生成を変える
	if (Data->GetMoveType() == MOVETYPE::STRAIGHT) {
		MovementBase* move = new StraightMove(VPos);

		//弾の発射方法によって生成を変える
		if (Data->GetShootType() == SHOOTTYPE::STRAIGHT) {

			//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
			tnl::Vector3 vecSpeed = { 0,10,0 };
			float coolDawn = 0.5f;

			ShootBase* shoot = new StraightShoot(vecSpeed, coolDawn);
			//特殊射撃を持たない敵ならそのまま生成
			if (Data->GetExShootType() == SHOOTTYPE::NONE) {
				return std::make_shared<Enemy>(StartPos, move, shoot);
			}
			else if (Data->GetExShootType() == SHOOTTYPE::STRAIGHT) {
				//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* exShoot = new StraightShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot,exShoot);
			}
			else if (Data->GetExShootType() == SHOOTTYPE::FOCUS) {
				//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* exShoot = new FocusShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot, exShoot);
			}
			else if (Data->GetExShootType() == SHOOTTYPE::FAST) {
				//弾の速度ベクトルとクールダウンはいずれCsvから読み取りたい
				tnl::Vector3 vecSpeed = { 0,10,0 };
				float coolDawn = 0.5f;

				ShootBase* exShoot = new StraightShoot(vecSpeed, coolDawn);
				return std::make_shared<Enemy>(StartPos, move, shoot, exShoot);
			}
		}
	}
	//else if (Move == MOVETYPE::STOPPOS) {
	//	MovementBase* move = new CenterStopMove(2.0f, gManager->Center);
	//	//弾の発射方法によって生成を変える
	//	if (Shoot == SHOOTTYPE::STRAIGHT) {

	//		tnl::Vector3 vecSpeed = { 0,10,0 };
	//		float coolDawn = 0.5f;

	//		ShootBase* shoot = new StraightShoot(vecSpeed, coolDawn);
	//		return std::make_shared<Enemy>(StartPos, move, shoot);
	//	}
	//}

}

//memo レーザー作る時に使う->tnl::IsIntersectRayOBB

/*
std::shared_ptr<Object> ObjectFactory::CreateObject(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	if (type == "Enemy") {
		return std::make_shared<Enemy>(StartPos);
	}
	else if (type == "Bullet") {
		return std::make_shared<Bullet>(StartPos, VPos);
	}
	return nullptr;
}
*/

Factory::Factory()
{
	tnl::DebugTrace("\nFactory親クラスが生成されました。\n");
	gManager = GameManager::Instance();
	eManager = EnemyManager::Instance();
}

//--------------------------Object型を生成する関数------------------------------------//
std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move)
{
	auto object = CreateObject(type, StartPos, VPos, Move, SHOOTTYPE::DUMMY);

	return object;
}
std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, ENEMYTYPE EnemyType)
{
	auto data = GetEnemyData(static_cast<int>(EnemyType));

	auto object = CreateObject(type, StartPos, VPos, , SHOOTTYPE::DUMMY);

	return object;
}

std::shared_ptr<Object> Factory::create(std::string type, const tnl::Vector3& StartPos, const tnl::Vector3& VPos, MOVETYPE Move, SHOOTTYPE Shoot)
{
	auto object = CreateObject(type, StartPos, VPos, Move, Shoot);

	return object;
}

std::shared_ptr<EnemyData> Factory::GetEnemyData(int EnemyType)
{
	return eManager->GetRandomEnemyData(EnemyType);
}

/*
//Objectを生成する関数 typeによって生成される継承先が異なる
std::shared_ptr<Object> Factory::create(std::string type, tnl::Vector3& StartPos, tnl::Vector3& VPos)
{
	auto p = CreateObject(type, StartPos, VPos);
	//std::shared_ptr<Object> p = CreateObject(type, StartPos, VPos);
	return p;
}
*/

//------------------------------------------------------------------------------------//

