#include "Player.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), PlayerTrans_(transform_),CamType_(0)
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("F_Player(move).fbx");
    assert(hModel_ >= 0);

    //�����ʒu�̐ݒ�
    PlayerTrans_.position_ = { 10.0f,0.0f,10.0f };

    //�A�j���[�V�������쏈��
    Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//�X�V
void Player::Update()
{
//������������������������������������������������������������������������������
//  �L�����N�^�[�̈ړ�����
//������������������������������������������������������������������������������

    /*�����������Ă�������̑���E�X�V������*/


    //�}�E�X�̈ړ��ʂ��擾
    XMFLOAT3 MouseMove_ = Input::GetMouseMove();
    PlayerTrans_.rotate_.y += (MouseMove_.x / 10.0f);

    /*�������� �O�㍶�E�̈ړ��E�X�V ��������*/

    //�����Ă���������擾

    //���_�̈ʒu��Player�̈ʒu������񂾃x�N�g�����쐬
    vPosition_ = XMLoadFloat3(&PlayerTrans_.position_);

    float Speed = 0.1f;
    //���_����Z�ɐ����ȃx�N�g�����쐬
    vMoveZ_ = { 0.0f,0.0f,Speed,0.0f };//{x,y,z,0}

    //���_����X�ɐ����ȃx�N�g�����쐬
    vMoveX_ = { Speed,0.0f,0.0f,0.0f };//{x,y,z,0}

    //transform_.rotate_.y�x��]������s����쐬
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(PlayerTrans_.rotate_.y));

    // vMoveZ / vMoveX ��RotateMatY�ŉ�]������
    vMoveZ_ = XMVector3TransformCoord(vMoveZ_, RotateMatY);
    vMoveX_ = XMVector3TransformCoord(vMoveX_, RotateMatY);

    //�uW�v�L�[�F�O�ɐi��
    if (Input::IsKey(DIK_W)) {
        vPosition_ += vMoveZ_;
        XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
    }

    //�uS�v�L�[�F���ɐi��
    if (Input::IsKey(DIK_S)) {
        vPosition_ -= vMoveZ_;
        XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
    }

    //�uA�v�L�[�F���ɐi��
    if (Input::IsKey(DIK_A)) {
        vPosition_ -= vMoveX_;
        XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
    }

    //�uD�v�L�[�F�E�ɐi��
    if (Input::IsKey(DIK_D)) {
        vPosition_ += vMoveX_;
        XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
    }

//������������������������������������������������������������������������������
//  �J�����̈ړ�����
//������������������������������������������������������������������������������

    //�J������ύX����
    if (Input::IsKeyDown(DIK_F4)) { CamChange(); }

    switch (CamType_)
    {
    case CAM_FIXED:	CamSet_FIXED();	break;
    case CAM_FPS:	CamSet_FPS();	break;
    }

    Camera::SetPosition(CamPosition_);
    Camera::SetTarget(CamTarget_);
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

//���_��ύX����֐�
void Player::CamChange()
{
    if (CamType_ < (CAM_MAX - 1))
        CamType_++;
    else
        CamType_ = 0;
}

//���_��ݒ肷��֐��F��l��
void Player::CamSet_FPS()
{
    //�J�����̈ʒu��player�̈ʒu�ɃZ�b�g
    XMVECTOR FPup = { 0.0f,1.0f,0.0f };
    XMStoreFloat3(&CamPosition_, vPosition_ + FPup);
    //�J�����̏œ_��player�̖ڐ�ɃZ�b�g
    XMStoreFloat3(&CamTarget_, vPosition_ + vMoveZ_ + FPup);
}

//���_��ݒ肷��֐��F�Œ�ʒu����̒Ǐ]
void Player::CamSet_FIXED()
{
    CamTarget_ = {PlayerTrans_.position_};
    CamPosition_ = { 10,10,-10 };
}
