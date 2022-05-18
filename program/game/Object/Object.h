#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;

class Object:public std::enable_shared_from_this<Object>
{
protected:
	//•`‰æÀ•W
	tnl::Vector3 pos;
	//‰æ‘œƒnƒ“ƒhƒ‹
	int gh = 0;

	//“–‚½‚è”»’è—p‚Ì”¼Œa(‰~‚Æ‰~‚ÌÕ“Ë‚Æ‚µ‚ÄÀ‘•‚·‚é)
	int radius = 0;

	GameManager* gManager = nullptr;

	bool isLive = true;

	//•ûŒü
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
	//¶€ó‘Ô‚ÌŠl“¾
	inline bool& GetIsLive() {
		return isLive;
	}

	inline void	SetIsLive() {
		isLive = false;
	}

	//•`‰æÀ•W‚Ìæ“¾
	inline tnl::Vector3& GetPos() {
		return pos;
	}
	//•`‰æÀ•W‚ÌƒZƒbƒg
	inline void	SetPos(tnl::Vector3 Pos) {
		pos = Pos;
	}

	//”¼Œa‚Ìæ“¾
	inline int& GetRadius() {
		return radius;
	}

	virtual~Object() {};

	//*******ƒˆ‰¼‘zŠÖ” Œp³æ‚ÅÀ‘•************//
	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Init() = 0;
	//¶€Šm”FŠÖ”
	virtual	void CheckIsLive() = 0;

private:


};

