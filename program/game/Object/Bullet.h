#pragma once
#include"Object.h"


class GameManager;

class Bullet:public Object
{
public:
	Bullet();
	~Bullet();

	void Update()override;
	void Draw()override;
	void Init()override;


private:

};

