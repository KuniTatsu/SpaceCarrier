#pragma once
#include<string>
#include<vector>
#include"../dxlib_ext/dxlib_ext.h"

class GameManager;
class Element;

class Menu
{
public:
	Menu() {};
	Menu(int MenuTopX, int MenuTopY, int Width,
		int Height, std::string GhPath);
	virtual~Menu() {};

	//�w�i�`��
	void MenuDraw();

	//������W�擾
	inline const tnl::Vector3& GetTopPos() {
		return menuTopPos;
	}

protected:
	//���j���[������W
	tnl::Vector3 menuTopPos = {};

	//���j���[����
	int width = 0;
	//���j���[�c��
	int height = 0;

	//���j���[�w�i�摜�p�X
	std::string menuBackGroundGhPass = "";
	//���j���[�w�i�摜�n���h��
	std::vector<int >menuBackGroundGh = {};

	GameManager* gManager = nullptr;
};

class SelectMenu :public Menu
{
public:
	SelectMenu(int TopX, int TopY, int Width, int Height, std::string GhPath);
	~SelectMenu();

	//menu���ڒǉ�
	void AddMenuElements(std::string Text);

	//menu�I���֐�
	void MenuUpdate();

	//menu�`��֐�
	void DrawSelectMenu();

	//���j���[�I��ԍ����擾����֐�
	inline int& GetNowSelectNum() {
		return nowSelectNum;
	}

	//���j���[�ԍ������Z�b�g����֐�
	inline void	ResetMenuNum() {
		nowSelectNum = 0;
	}

private:

	////���j���[����
	//std::vector <std::string>menuElements;

	//�I�𒆂̃��j���[�ԍ�
	int nowSelectNum = 0;

	//���j���[���ڕ\���̂��߂̍��ォ��̃I�t�Z�b�g����
	const tnl::Vector3 OFFSET = { 10,10,0 };

	//���j���[���ڕ\���̂��߂̊e���ڊԋ���
	const int DISTANCE = 20;


	//���j���[���ڂ̃n�C���C�g�摜�n���h��
	int highLightGh = 0;

	//menuElement�̃|�C���^�z��
	std::vector<std::unique_ptr<Element>>elements;

};

//--------------Menu����,�w�i�摜,�����蔻��p�N���X--------------//
class Element
{
public:
	Element(float CenterX, float CenterY, std::string Text);
	~Element();
	//���j���[���ڂ̕`��
	void DrawElement();

	//���S���W
	tnl::Vector3 centerPos = {};

	//���[�̍��W
	tnl::Vector3 leftPos = {};

	//�`�悷��e�L�X�g
	std::string element="";

	//�`��摜 50x20
	int gh = 0;

	//�e�L�X�g�G���A�̑傫��
	const tnl::Vector3 TEXTRECT = { 100,20,0 };

	//gamemanager
	GameManager* gManager = nullptr;
};

