#pragma once
#include"Object.h"
#include<memory>
#include<math.h>

class GameManager;

class Player final :public Object
{
public:
	Player();
	~Player();

	void Update()override;
	void Draw()override;
	void Init()override;
	

private:

	void Move();


	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};
	const tnl::Input::eKeys arrowKeys[static_cast<int>(DIR::MAX)] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT, tnl::Input::eKeys::KB_DOWN, tnl::Input::eKeys::KB_LEFT };

	inline tnl::Input::eKeys GetKeys(int KeyNum){
		return arrowKeys[KeyNum];
	}

	//void SetMoveAmount();

	float moveX = 0.0f;
	float moveY = 0.0f;
	float fixMoveAmount = 0.0f;

	const int SPEED = 5;

	//ˆÚ“®ƒL[‚ğ‰Ÿ‚µ‚½‚Æ‚«‚ÌˆÚ“®—Ê
	const int MOVEAMOUNT[static_cast<int>(DIR::MAX)] = { -SPEED,SPEED,SPEED,-SPEED };


	inline tnl::Vector3 GetFixVector(float X, float Y) {

		float vecLength = std::sqrt(X * X + Y * Y);
		
		return tnl::Vector3(X / vecLength, Y / vecLength, 0);

	}
	

};

