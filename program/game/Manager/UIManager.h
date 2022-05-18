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

	//UI�̍X�V �I�񂾗v�f�ԍ�������int�^�Q�Ƃ������ɓ����
	void UpdateUI(int& SelectNum);
	//UI�̕`��
	void DrawUI();

	//UI�̓o�^
	inline void	SetUIList(std::shared_ptr<GraphicUI>Ui) {
		uiList.emplace_back(Ui);
	}
private:

	GameManager* gManager = nullptr;
	//�`�悷��UI�̃��X�g
	std::vector<std::shared_ptr<GraphicUI>>uiList;

	//�I�𒆂̗v�f�ԍ�
	int nowSelect = 0;

	//�I�𒆂̗v�f���w���J�[�\���̉摜�n���h��
	int CursorGh = 0;
	
	//�J�[�\���̕`��{��
	float cursorDrawEx = 1.0f;

	//UI����ׂ����
	enum class DRAWDIR {
		HORIZONTAL,
		VERTICAL,
		MAX
	};

	//����UI�̕`�����
	DRAWDIR setDir = DRAWDIR::HORIZONTAL;

	//�������̑I��UI�ړ��֐�
	void MoveSelectHorizontal();
	//�c�����̑I��UI�ړ��֐�
	void MoveSelectVertical();

	//����L�[����������ɗv�f�ԍ���Ԃ��֐�
	inline int GetSelectNum() {
		return nowSelect;
	};
};
