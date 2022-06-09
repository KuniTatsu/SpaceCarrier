#include"SceneManager.h"
#include <cstddef>
#include"DxLib.h"
#include"../Scene/TitleScene.h"
#include"../Scene/InGameScene.h"
#include"../Scene/CustomizeScene.h"
#include"../Scene/StageSelectScene.h"


BaseScene* SceneManager::nowScene = NULL;       //始めはシーンは空

void SceneManager::ChangeScene(SCENE Scene) {

    if (nowScene != NULL) {
        delete nowScene;
    }

    switch (Scene) {          //引数のシーン
    case SCENE::TITLE:
        nowScene = new TitleScene();          //タイトルシーンを現在のシーンにする
        break;
    case SCENE::INGAME:
        nowScene = new InGameScene();         //インゲームシーンを現在のシーンにする
        break;
    case SCENE::SELECT:
        nowScene = new StageSelectScene();     //ステージセレクトシーンを現在のシーンにする
        break;
    case SCENE::CUSTOM:
        nowScene = new CustomizeScene();        //カスタマイズシーンを現在のシーンにする
    default:
        break;
    }

}

void SceneManager::Update() {
    nowScene->Update();         //現在のシーンの更新関数
}

void SceneManager::Render() {
    nowScene->Draw();           //現在のシーンの描画関数
}

void SceneManager::Save()
{
    nowScene->Save();


}

void SceneManager::Load()
{
    nowScene->Load();
}
