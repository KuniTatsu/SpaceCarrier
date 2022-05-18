#include "UIManager.h"
#include"../GraphicUI.h"
#include"GameManager.h"


UIManager::UIManager(int DrawDir)
{
	gManager = GameManager::Instance();
	if (DrawDir == 0) {
		setDir = DRAWDIR::HORIZONTAL;
		CursorGh = gManager->LoadGraphEx("graphics/SelectCursorHorizontal.png");
	}
	else {
		setDir = DRAWDIR::VERTICAL;
		CursorGh = gManager->LoadGraphEx("graphics/SelectCursorVertical.png");
	}
}

UIManager::~UIManager()
{
}

void UIManager::UpdateUI(int& SelectNum)
{
	if (setDir == DRAWDIR::HORIZONTAL)MoveSelectHorizontal();
	else MoveSelectVertical();

	//Enterを押すと選んでいるUIの要素番号を返す
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) {
		SelectNum = GetSelectNum();
	}
}

void UIManager::DrawUI()
{
	for (auto ui : uiList) {
		ui->Draw();
	}
	//カーソルの描画
	DrawRotaGraph(uiList[nowSelect]->GetCenterPos().x, uiList[nowSelect]->GetUnderBottomPos(), cursorDrawEx, 0, CursorGh, true);
}
//左右方向のUIの移動関数
void UIManager::MoveSelectHorizontal()
{
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_LEFT)) {
		nowSelect = (nowSelect + (uiList.size() - 1)) % uiList.size();
	}
	else if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RIGHT)) {
		nowSelect = (nowSelect + 1) % uiList.size();
	}
}
//上下方向のUIの移動関数
void UIManager::MoveSelectVertical()
{
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_UP)) {
		nowSelect = (nowSelect + (uiList.size() - 1)) % uiList.size();
	}
	else if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_DOWN)) {
		nowSelect = (nowSelect + 1) % uiList.size();
	}
}

