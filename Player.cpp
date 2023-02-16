#include "Player.h"

#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), PlayerTrans_(transform_)
{
}

//������
void Player::Initialize()
{
    hModel_ = Model::Load("F_Player(move).fbx");
    assert(hModel_ >= 0);

    Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//�X�V
void Player::Update()
{
//������������������������������������������������������������������������������
//  �L�����N�^�[�̈ړ�����
//������������������������������������������������������������������������������

    /*�����������Ă�������̑���E�X�V������*/
     //�u���v�L�[�F�������ɉ�]
    if (Input::IsKey(DIK_LEFT)) {
        PlayerTrans_.rotate_.y -= 2.0f;
    }
    //�u���v�L�[�F�E�����ɉ�]
    if (Input::IsKey(DIK_RIGHT)) {
        PlayerTrans_.rotate_.y += 2.0f;
    }

    /*�������� �O�㍶�E�̈ړ��E�X�V ��������*/

    //�����Ă���������擾

    //���_�̈ʒu��Player�̈ʒu������񂾃x�N�g�����쐬
    XMVECTOR vPosition = XMLoadFloat3(&PlayerTrans_.position_);

    //���_����Z�ɐ����ȃx�N�g�����쐬
    XMVECTOR vMoveZ = { 0.0f,0.0f,0.05f,0.0f };//{x,y,z,0}

    //���_����X�ɐ����ȃx�N�g�����쐬
    XMVECTOR vMoveX = { 0.05f,0.0f,0.0f,0.0f };//{x,y,z,0}

    //transform_.rotate_.y�x��]������s����쐬
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(PlayerTrans_.rotate_.y));

    // vMoveZ / vMoveX ��RotateMatY�ŉ�]������
    vMoveZ = XMVector3TransformCoord(vMoveZ, RotateMatY);
    vMoveX = XMVector3TransformCoord(vMoveX, RotateMatY);

    //�uW�v�L�[�F�O�ɐi��
    if (Input::IsKey(DIK_W)) {
        vPosition += vMoveZ;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&PlayerTrans_.position_, vPosition);
    }

    //�uS�v�L�[�F���ɐi��
    if (Input::IsKey(DIK_S)) {
        vPosition -= vMoveZ;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&PlayerTrans_.position_, vPosition);
    }

    //�uA�v�L�[�F���ɐi��
    if (Input::IsKey(DIK_A)) {
        vPosition -= vMoveX;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&PlayerTrans_.position_, vPosition);
    }

    //�uD�v�L�[�F�E�ɐi��
    if (Input::IsKey(DIK_D)) {
        vPosition += vMoveX;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&PlayerTrans_.position_, vPosition);
    }
}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, PlayerTrans_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}
