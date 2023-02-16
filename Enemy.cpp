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
	hModel_ = Model::Load("F_Player(move).fbx");
	assert(hModel_ >= 0);

	Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//�X�V
void Enemy::Update()
{
//������������������������������������������������������������������������������
//  �L�����N�^�[�̈ړ�����
//������������������������������������������������������������������������������

    /*�����������Ă�������̑���E�X�V������*/
    RotateRight();  //�u���v�L�[�F�E�����ɉ�]
    RotateLeft();   //�u���v�L�[�F�������ɉ�]

    /*�������� �O�㍶�E�̈ړ��E�X�V ��������*/

    //�����Ă���������擾

    //���_�̈ʒu��Enemy�̈ʒu������񂾃x�N�g�����쐬
    XMVECTOR vPosition = XMLoadFloat3(&EnemyTrans_.position_);

    //���_����Z�ɐ����ȃx�N�g�����쐬
    XMVECTOR vMoveZ = { 0.0f,0.0f,0.05f,0.0f };//{x,y,z,0}

    //���_����X�ɐ����ȃx�N�g�����쐬
    XMVECTOR vMoveX = { 0.05f,0.0f,0.0f,0.0f };//{x,y,z,0}

    //transform_.rotate_.y�x��]������s����쐬
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(EnemyTrans_.rotate_.y));

    // vMoveZ / vMoveX ��RotateMatY�ŉ�]������
    vMoveZ = XMVector3TransformCoord(vMoveZ, RotateMatY);
    vMoveX = XMVector3TransformCoord(vMoveX, RotateMatY);

    //�uW�v�L�[�F�O�ɐi��
    if (Input::IsKey(DIK_W)) {
        vPosition += vMoveZ;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&EnemyTrans_.position_, vPosition);
    }

    //�uS�v�L�[�F���ɐi��
    if (Input::IsKey(DIK_S)) {
        vPosition -= vMoveZ;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&EnemyTrans_.position_, vPosition);
    }

    //�uA�v�L�[�F���ɐi��
    if (Input::IsKey(DIK_A)) {
        vPosition -= vMoveX;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&EnemyTrans_.position_, vPosition);
    }

    //�uD�v�L�[�F�E�ɐi��
    if (Input::IsKey(DIK_D)) {
        vPosition += vMoveX;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&EnemyTrans_.position_, vPosition);
    }
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

void Enemy::RotateRight()
{
    if (Input::IsKey(DIK_RIGHT)) {
        EnemyTrans_.rotate_.y += 2.0f;
    }
}

void Enemy::RotateLeft()
{
    if (Input::IsKey(DIK_LEFT)) {
        EnemyTrans_.rotate_.y -= 2.0f;
    }
}

/*
float Speed = 0.01f;
//�ړ��F�E
if (Input::IsKey(DIK_D))
{
    transform_.position_.x += Speed;
    transform_.rotate_.y = 90.0f;
}

//�ړ��F��
if (Input::IsKey(DIK_A))
{
    transform_.position_.x -= Speed;
    transform_.rotate_.y = -90.0f;
}

//�ړ��F��
if (Input::IsKey(DIK_W))
{
    transform_.position_.z += Speed;
    transform_.rotate_.y = 0.0f;
}

//�ړ��F��O
if (Input::IsKey(DIK_S))
{
    transform_.position_.z -= Speed;
    transform_.rotate_.y = -180.0f;
}
*/

////�u���v�L�[�������ƉE��]
//if (Input::IsKey(DIK_RIGHT))
//{
//    transform_.rotate_.y += 2.0f;
//}
////�u���v�L�[�������ƍ���]
//if (Input::IsKey(DIK_LEFT))
//{
//    transform_.rotate_.y -= 2.0f;
//}
//
////���ݒn���x�N�g���^�ɕϊ�
//XMVECTOR VectorPos = XMLoadFloat3(&transform_.position_);
////�P�t���[���̈ړ��x�N�g��
//XMVECTOR VectorMove = { 0.0f,0.0f,0.10f,0.0f };
////transform_.rotate_.y�x��]������s����쐬
//XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
//XMMATRIX RotateMatYL = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y - 90));
//
//
////�uW�v�L�[�������ƌ����Ă�������ɐi��
//if (Input::IsKey(DIK_W))
//{
//    //�ړ��x�N�g����ό`(���������ɉ�])
//    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatY);
//    //�����Ă�������ɐi�ޏ���
//    //�ړ�
//    VectorPos += (VectorMove);
//    //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
//    XMStoreFloat3(&transform_.position_, VectorPos);
//}
//
////�uS�v�L�[�������ƌ����Ă�������̌��ɐi��
//if (Input::IsKey(DIK_S))
//{
//    //�ړ��x�N�g����ό`(���������ɉ�])
//    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatY);
//    //�ړ�
//    VectorPos -= VectorMove;
//    //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
//    XMStoreFloat3(&transform_.position_, VectorPos);
//}
//
////�uA�v�L�[�������ƌ����Ă�������̍��ɐi��
//if (Input::IsKey(DIK_A))
//{
//    //�ړ��x�N�g����ό`(���������ɉ�])
//    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatYL);
//    //�ړ�
//    VectorPos += VectorMove;
//    //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
//    XMStoreFloat3(&transform_.position_, VectorPos);
//}
//
////�uD�v�L�[�������ƌ����Ă�������̉E�ɐi��
//if (Input::IsKey(DIK_A))
//{
//    //�ړ��x�N�g����ό`(���������ɉ�])
//    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatYL);
//    //�ړ�
//    VectorPos -= VectorMove;
//    //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
//    XMStoreFloat3(&transform_.position_, VectorPos);
//}
////��������������������������������������������������