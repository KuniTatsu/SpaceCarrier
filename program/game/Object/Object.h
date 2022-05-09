#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;

class Object:public std::enable_shared_from_this<Object>
{
protected:
	//�`����W
	tnl::Vector3 pos;
	//�摜�n���h��
	int gh = 0;

	GameManager* gManager = nullptr;
public:
	Object();

	void SetList();

	virtual~Object() {};

	//*******�������z�֐� �p����Ŏ���************//
	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Init() = 0;

private:


};

