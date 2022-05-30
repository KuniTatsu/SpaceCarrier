//船のパーツを管理するマネージャクラス
//シングルトンで作られている
#pragma once
#include<vector>
#include<list>
#include<string>
#include<unordered_map>
#include"../../dxlib_ext/dxlib_ext.h"
#include<memory>

class PartsBase;
class ShipParts;
class WeaponParts;

class PartsManager {

protected:
	PartsManager();
	~PartsManager();
public:
	//インスタンスがなければ生成、あれば返す関数
	static PartsManager* Instance();

	//初期化
	void Init();
	//Csvロード
	void LoadCsv();

	//パーツコード
	enum class PARTSCODE:uint32_t {
		HULL,
		CONTAINER,
		ARMOR,
		GENERATOR,
		THRUSTER,
		MAX
	};
	//初期パーツ格納関数
	void SetProtoTypeParts(std::vector<std::shared_ptr<PartsBase>>& PartsSet);
	//初期武器格納関数
	void SetProtoTypeWeapon(std::vector<std::shared_ptr<PartsBase>>& WeaponSet);

	//パーツデータ取得関数


private:
	//シングルトンインスタンス
	static PartsManager* instance;

	std::vector<std::vector<std::string>> loadPartsCsv;

	std::vector<std::vector<std::string>> loadWeaponPartsCsv;

	//船体パーツマスター
	std::vector<std::vector<std::shared_ptr<ShipParts>>>shipPartsMaster;
	//武器パーツマスター
	std::vector<std::vector<std::shared_ptr<WeaponParts>>>weaponPartsMaster;

};