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

	//���C�L���X�g(�r�[��)�𐳖ʂ����΂�

	//�ǂɂԂ�������E�A���A���Ƀ��C���΂�
	//������Ȃ��������ɉ�]���A�i��
	//�����ǂ���Ƃ�������Ȃ�������A�����_���ɂ��āA�E�A���A���ɐi��
	//player�ɓ���������Aplayer�̍��W���擾���Ă����Ɍ�����

//������������������������������������������������������������������������������
//  �L�����N�^�[�̐ڐG����
//������������������������������������������������������������������������������

	//player�ƐڐG�����Ƃ��Aplayer���L������
	//���̊
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