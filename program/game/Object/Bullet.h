#pragma once
#include"Object.h"


class GameManager;
class BulletManager;

class Bullet:public Object
{
public:
	Bullet() {};
	Bullet(tnl::Vector3& StartPos, tnl::Vector3& VPos);
	~Bullet();

	void Update()override;
	void Draw()override;
	void Init()override;

	void Initialize(tnl::Vector3& StartPos, tnl::Vector3& VPos);

	void CheckIsLive()override;


private:
	//BulletManager�̃C���X�^���X
	BulletManager* bManager = nullptr;


	//�ړ��x�N�g��
	tnl::Vector3 vPos = {};


	

};

