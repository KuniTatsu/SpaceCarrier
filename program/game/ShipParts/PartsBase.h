#pragma once
#include<string>

class GameManager;
class ModManager;
class PartsBase
{
public:
	PartsBase() {};
	virtual ~PartsBase() {};

	//パーツId取得
	inline int& GetPartsId() {
		return partsId;
	}
	//パーツタイプ取得
	inline int& GetPartsType() {
		return partsType;
	}
	//パーツ名取得
	inline std::string& GetPartsName() {
		return partsName;
	}
	//画像ハンドルのパス取得
	inline std::string& GetPartsGhPass() {
		return pass;
	}
	//アイコン画像のパス取得
	inline std::string& GetIconGhPass() {
		return iconPass;
	}

	//装備状態を切り替える関数
	inline void	ChangeEquiped() {
		//装備していたら
		if (isEquiped)
		{
			//装備状態を外す
			isEquiped = false;
			return;
		}
		isEquiped = true;
	}


	//装備状況を返す関数
	inline bool IsEquiped() {
		return isEquiped;
	}


	//船改造画面での描画関数
	virtual void DrawParts(int X,int Y) = 0;

protected:
	//id
	int partsId = 0;
	//パーツタイプ
	int partsType = 0;
	//パーツ名
	std::string	partsName = "";

	//ghPass
	std::string pass = "";
	//gh
	int gh = 0;

	//IconGhPass
	std::string iconPass = "";
	//iconGh
	int iconGh = 0;

	//iconBackGh
	int iconBachGh = 0;

	//equipIconGh
	int iconEquipGh = 0;

	//装備されているかどうか
	bool isEquiped = false;

	//ゲームマネージャポインタ
	GameManager* gManager = nullptr;

	//ModManagerポインタ
	ModManager* mManager = nullptr;
};

