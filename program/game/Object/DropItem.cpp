#include "DropItem.h"
#include"../StrategyPattern/MovementPattern.h"
#include"../Manager/GameManager.h"
#include"../Object/Player.h"

DropItem::DropItem(float startPosX, float startPosY)
{
	pos.x = startPosX;
	pos.y = startPosY;

	Init();
}

DropItem::~DropItem()
{
}

void DropItem::Update()
{
	pos = myMove->Move(pos);
}

void DropItem::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, gh, true);
}

void DropItem::Init()
{
	//“®‚«•û‚ð¶¬
	//MovementBase* track = new ToTargetMove(VPos, target);

	auto player = gManager->GetPlayer();
	myMove = std::make_shared<ToTargetMove>(tnl::Vector3(0, 10, 0),player );

	//‰æ‘œƒ[ƒh
	gh = gManager->LoadGraphEx("graphics/DropItem.png");

	player = gManager->GetPlayer();
	radius = 25;
}

void DropItem::CheckIsLive()
{
	//
}
