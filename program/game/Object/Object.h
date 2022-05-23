#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;

class Object :public std::enable_shared_from_this<Object>
{
protected:
	//�`����W
	tnl::Vector3 pos;
	//�摜�n���h��
	int gh = 0;

	//���x�x�N�g��
	tnl::Vector3 vecSpeed = {};

	//�����蔻��p�̔��a(�~�Ɖ~�̏Փ˂Ƃ��Ď�������)
	float radius = 0;

	GameManager* gManager = nullptr;

	bool isLive = true;

	//����
	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};
public:
	Object();

	void SetList();
	//������Ԃ̊l��
	inline bool& GetIsLive() {
		return isLive;
	}

	inline void	SetIsLive() {
		isLive = false;
	}

	//�`����W�̎擾
	inline tnl::Vector3& GetPos() {
		return pos;
	}
	//�`����W�̃Z�b�g
	inline void	SetPos(tnl::Vector3 Pos) {
		pos = Pos;
	}

	//���a�̎擾
	inline float& GetRadius() {
		return radius;
	}

	//���x�x�N�g���擾�֐�
	inline tnl::Vector3 GetVecSpeed() {
		return vecSpeed;
	}

	virtual~Object() {};

	//*******�������z�֐� �p����Ŏ���************//
	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Init() = 0;
	//�����m�F�֐�
	virtual	void CheckIsLive() = 0;

private:
};

