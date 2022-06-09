#include"SceneManager.h"
#include <cstddef>
#include"DxLib.h"
#include"../Scene/TitleScene.h"
#include"../Scene/InGameScene.h"
#include"../Scene/CustomizeScene.h"
#include"../Scene/StageSelectScene.h"


BaseScene* SceneManager::nowScene = NULL;       //�n�߂̓V�[���͋�

void SceneManager::ChangeScene(SCENE Scene) {

    if (nowScene != NULL) {
        delete nowScene;
    }

    switch (Scene) {          //�����̃V�[��
    case SCENE::TITLE:
        nowScene = new TitleScene();          //�^�C�g���V�[�������݂̃V�[���ɂ���
        break;
    case SCENE::INGAME:
        nowScene = new InGameScene();         //�C���Q�[���V�[�������݂̃V�[���ɂ���
        break;
    case SCENE::SELECT:
        nowScene = new StageSelectScene();     //�X�e�[�W�Z���N�g�V�[�������݂̃V�[���ɂ���
        break;
    case SCENE::CUSTOM:
        nowScene = new CustomizeScene();        //�J�X�^�}�C�Y�V�[�������݂̃V�[���ɂ���
    default:
        break;
    }

}

void SceneManager::Update() {
    nowScene->Update();         //���݂̃V�[���̍X�V�֐�
}

void SceneManager::Render() {
    nowScene->Draw();           //���݂̃V�[���̕`��֐�
}

void SceneManager::Save()
{
    nowScene->Save();


}

void SceneManager::Load()
{
    nowScene->Load();
}
