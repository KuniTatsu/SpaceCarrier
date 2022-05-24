#pragma once
#include"../../dxlib_ext/dxlib_ext.h"
#include<memory>
class Factory;
class GameManager;

//----------�ړ����@�̃x�[�X�N���X------------
class ShootBase
{
public:
	ShootBase();
	virtual~ShootBase();
	//�ړ��֐� ���z�֐�
	virtual bool Shoot(tnl::Vector3 Pos, int Radius, float Deltatime) = 0;
protected:

	Factory* fac = nullptr;
	GameManager* gManager = nullptr;

	//�e�̐i�ޑ��x�x�N�g��
	tnl::Vector3 vecSpeed = {};
	//���̔��˂܂ł̕K�v�N�[���_�E��
	float COOLTIME = 0;
	//�e�����N�[���_�E���^�C��
	float coolDown = 0.0f;

	//�N�[���_�E���m�F�֐�
	bool CheckCoolDawn(const float Deltatime);
};
//------------vecspeed�����x�N�g���֒��i����N���X-------------
class StraightShoot :public ShootBase
{
public:
	StraightShoot(tnl::Vector3 VecSpeed, float CoolDawn);
	~StraightShoot()override;

	bool Shoot(tnl::Vector3 Pos, int Radius, float Deltatime)override;
};
//------------���^�C�~���O�Ńv���C���[�����������ɕ��N���X-----------
class FocusShoot :public ShootBase
{
public:
	FocusShoot(tnl::Vector3 VecSpeed, float CoolDawn);
	~FocusShoot()override;

	bool Shoot(tnl::Vector3 Pos, int Radius, float Deltatime)override;
};
//------------�N�[���_�E�����Z���e�������񂾂񑁂��Ȃ�N���X------------
class FastShoot :public ShootBase
{
public:
	FastShoot(tnl::Vector3 VecSpeed, float CoolDawn);
	~FastShoot()override;

	bool Shoot(tnl::Vector3 Pos, int Radius, float Deltatime)override;
};

//------------�ǔ�����e�̃N���X------------
class TrackShoot :public ShootBase
{
public:
	TrackShoot(tnl::Vector3 VecSpeed, float CoolDawn);
	~TrackShoot()override;

	bool Shoot(tnl::Vector3 Pos, int Radius, float Deltatime)override;
};