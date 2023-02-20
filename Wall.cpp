#include "Wall.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Wall::Wall(GameObject* parent)
	: GameObject(parent, "Wall"), hModel_(-1)
{
}

//������
void Wall::Initialize()
{
		//���f���f�[�^�̃��[�h
		hModel_ = Model::Load("F_Wall.fbx");
		assert(hModel_ >= 0);
}

//�X�V
void Wall::Update()
{
}

//�`��
void Wall::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Wall::Release()
{
}