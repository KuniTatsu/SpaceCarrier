#include "Movement.h"

MovementBase::MovementBase()
{
}

MovementBase::~MovementBase()
{
}

StraightMove::StraightMove(tnl::Vector3 VecSpeed)
{
	vecSpeed = VecSpeed;
}

StraightMove::~StraightMove()
{
}

tnl::Vector3 StraightMove::Move(tnl::Vector3 pos)
{
	return pos + vecSpeed;
}
