#include "Enemy.h"

#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1), EnemyTrans_(transform_)
{
}

//������
void Enemy::Initialize()
{
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//�X�V
void Enemy::Update()
{
//������������������������������������������������������������������������������
//  �L�����N�^�[�̈ړ�����
//������������������������������������������������������������������������������
}

//�`��
void Enemy::Draw()
{
	Model::SetTransform(hModel_, EnemyTrans_);
	Model::Draw(hModel_);
}

//�J��
void Enemy::Release()
{
}