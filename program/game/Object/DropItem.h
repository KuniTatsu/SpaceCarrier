//Ingame���Ńh���b�v���Aplayer�܂ňړ���������������
//�h���b�v�A�C�e���̃N���X

#pragma once
#include"Object.h"
#include<memory>

class MovementBase;
class Player;

class DropItem :Object
{
public:
	DropItem() {};
	DropItem(float startPosX, float startPosY);
	~DropItem();

	void Update()override;

	void Draw()override;

	void Init()override;
	//�����m�F�֐�
	void CheckIsLive()override;

	inline float& GetRadius() {
		return radius;
	}

	inline bool GetIsLive() {
		return isLive;
	}

private:
	//������ player��ǔ�����
	std::shared_ptr<MovementBase>myMove = nullptr;

	//player�C���X�^���X
	std::shared_ptr<Player>player = nullptr;
};

