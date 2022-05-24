#pragma once
#include<string>

class GameManager;
class PartsBase
{
public:
	PartsBase() {};
	virtual ~PartsBase() {};

	//パーツId取得
	inline int GetPartsId() {
		return partsId;
	}
	//パーツタイプ取得
	inline int GetPartsType() {
		return partsType;
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

	//gh
	int gh = 0;

	//ゲームマネージャポインタ
	GameManager* gManager = nullptr;
};

