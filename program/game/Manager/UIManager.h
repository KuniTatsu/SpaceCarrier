#pragma once
#include<vector>
#include<memory>

class GraphicUI;
class GameManager;

class UIManager
{
public:
	UIManager(int DrawDir);
	~UIManager();

	//UIの更新 選んだ要素番号を入れるint型参照を引数に入れる
	void UpdateUI(int& SelectNum);
	//UIの描画
	void DrawUI();

	//UIの登録
	inline void	SetUIList(std::shared_ptr<GraphicUI>Ui) {
		uiList.emplace_back(Ui);
	}
private:

	GameManager* gManager = nullptr;
	//描画するUIのリスト
	std::vector<std::shared_ptr<GraphicUI>>uiList;

	//選択中の要素番号
	int nowSelect = 0;

	//選択中の要素を指すカーソルの画像ハンドル
	int CursorGh = 0;
	
	//カーソルの描画倍率
	float cursorDrawEx = 1.0f;

	//UIを並べる方向
	enum class DRAWDIR {
		HORIZONTAL,
		VERTICAL,
		MAX
	};

	//このUIの描画方向
	DRAWDIR setDir = DRAWDIR::HORIZONTAL;

	//横方向の選択UI移動関数
	void MoveSelectHorizontal();
	//縦方向の選択UI移動関数
	void MoveSelectVertical();

	//決定キーを押した後に要素番号を返す関数
	inline int GetSelectNum() {
		return nowSelect;
	};
};
