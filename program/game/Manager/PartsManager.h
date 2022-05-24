//船のパーツを管理するマネージャクラス
//シングルトンで作られている
#pragma once
#include<vector>
#include<list>
#include<string>
#include<unordered_map>
#include"../../dxlib_ext/dxlib_ext.h"
#include<memory>

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