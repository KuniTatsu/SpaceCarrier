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

	//ゲームマネージャポインタ
	GameManager* gManager = nullptr;

	//ModManagerポインタ
	ModManager* mManager = nullptr;
};

