#include "Animation.h"
#include"Manager/GameManager.h"

Animation::Animation(std::string Gh, tnl::Vector3 Pos, int ActSpeed, int MaxIndex, int XNum, int YNum, int XSize, int YSize)
{
	//�Q�[���}�l�[�W���C���X�^���X�擾
	gManager = GameManager::Instance();
	//�摜�̕������[�h
	gManager->LoadDivGraphEx(Gh, MaxIndex, XNum, YNum, XSize, YSize, animGh);

	pos = Pos;
	actSpeed = ActSpeed;
	maxMotionIndex = MaxIndex;
}

Animation::~Animation()
{
}

void Animation::Update()
{
	//�`�悷��摜��I������
	if (--actWait <= 0) {
		actIndex++;
		actWait = actSpeed;
		actIndex %= maxMotionIndex;
		//tnl::DebugTrace("\n�A�j���[�V�����X�V%d���\n", actIndex);
	}
	else return;
	//�摜�X�V
	drawGh = animGh[actIndex];
	//�A�j���[�V�����I������
	if (drawGh == animGh[maxMotionIndex - 1])isAlive = false;

}

void Animation::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawRotaGraph(pos.x, pos.y, 1, 0, drawGh, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
