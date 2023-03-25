#include "Player.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), PlayerTrans_(transform_),CamType_(0),moving_(0)
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("F_Player(move).fbx");
    assert(hModel_ >= 0);

    HRFrame_ = Image::Load("P_hFrame2.png");
    assert(HRFrame_ >= 0);

    //�����ʒu�̐ݒ�
    PlayerTrans_.position_ = { 3.0f,0.0f,3.0f };

    //�A�j���[�V�������쏈��
    Model::SetAnimFrame(hModel_, 0, 60, 1);

    pStageMap = (StageMap*)FindObject("StageMap");
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

        //�ړ����x
        float Speed = 0.09f;
        if (Input::IsKey(DIK_LSHIFT)) { Speed = 0.1f; }

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
            XMVector3Normalize(vMoveZ_);//�ړ��x�N�g���𐳋K��
        }

        //�uS�v�L�[�F���ɐi��
        if (Input::IsKey(DIK_S)) {
            vPosition_ -= vMoveZ_;
            XMVector3Normalize(vMoveZ_);//�ړ��x�N�g���𐳋K��
        }

        //�uA�v�L�[�F���ɐi��
        if (Input::IsKey(DIK_A)) {
            vPosition_ -= vMoveX_;
            XMVector3Normalize(vMoveX_);//�ړ��x�N�g���𐳋K��
        }

        //�uD�v�L�[�F�E�ɐi��
        if (Input::IsKey(DIK_D)) {
            vPosition_ += vMoveX_;
            XMVector3Normalize(vMoveX_);//�ړ��x�N�g���𐳋K��
        }

        XMVector3Normalize(vPosition_);//�ړ��x�N�g���𐳋K��
        XMStoreFloat3(&PlayerTrans_.position_, vPosition_);

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
    
//������������������������������������������������������������������������������
//  �����蔻��
//������������������������������������������������������������������������������

    //�f�o�b�N�p
    //Player(���S)���ǂƐڐG���Ă��邩���m�F����
    #if 1
    {
        if (pStageMap->isWall(PlayerTrans_.position_.x, PlayerTrans_.position_.z)){
            Debug::Log("�Z",true);}
        else{
            Debug::Log("��", true);}
    
    }
    #endif

    //�����蔻��̊e���_���\������v�f
    int checkX1, checkZ1;
    int checkX2, checkZ2;

    //�����蔻��̊e����
    #if 0
    {
        //�E���̔���
        {
            //���_�P���\��
            checkX1 = (int)(PlayerTrans_.position_.x + 0.2f);
            checkZ1 = (int)(PlayerTrans_.position_.z + 0.1f);

            //���_�Q���\��
            checkX2 = (int)(PlayerTrans_.position_.x + 0.2f);
            checkZ2 = (int)(PlayerTrans_.position_.z - 0.1f);

            //���_�P,�Q���ǂ��ǂ����𔻒肷��
            if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)){
                PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + (1.0f - 0.2f);
            }
        }

        //�����̔���
        {
            //���_�P���\��
            checkX1 = (int)(PlayerTrans_.position_.x - 0.2f);
            checkZ1 = (int)(PlayerTrans_.position_.z + 0.1f);

            //���_�Q���\��
            checkX2 = (int)(PlayerTrans_.position_.x - 0.2f);
            checkZ2 = (int)(PlayerTrans_.position_.z - 0.1f);

            //�������ǂ��ǂ����𔻒肷��
            if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)){
                PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + 0.2f;
            }
        }

        //�����̔���
        {
            //���_�P���\��
            checkX1 = (int)(PlayerTrans_.position_.x + 0.1f);
            checkZ1 = (int)(PlayerTrans_.position_.z + 0.2f);

            //���_�Q���\��
            checkX2 = (int)(PlayerTrans_.position_.x - 0.1f);
            checkZ2 = (int)(PlayerTrans_.position_.z + 0.2f);

            //�������ǂ��ǂ����𔻒肷��
            if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)){
                PlayerTrans_.position_.z = (float)((int)PlayerTrans_.position_.z) + (1.0f - 0.2f);
            }
        }

        //�O���̔���
        {
            //���_�P���\��
            checkX1 = (int)(PlayerTrans_.position_.x + 0.1f);
            checkZ1 = (int)(PlayerTrans_.position_.z - 0.2f);

            //���_�Q���\��
            checkX2 = (int)(PlayerTrans_.position_.x - 0.1f);
            checkZ2 = (int)(PlayerTrans_.position_.z - 0.2f);

            //�������ǂ��ǂ����𔻒肷��
            if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)){
                PlayerTrans_.position_.z = (float)((int)PlayerTrans_.position_.z) + 0.2f;
            }
        }
    }
    #endif

}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, PlayerTrans_);
    Model::Draw(hModel_);

    /*Image::SetTransform(HRFrame_, transform_);
    Image::Draw(HRFrame_);*/
}

//�J��
void Player::Release()
{
}

//Player�̌��ݒn���擾����֐�
XMFLOAT3 Player::GetPosition()
{
    return(this->PlayerTrans_.position_);
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
    XMVECTOR FPup = { 0.0f,1.2f,0.0f };
    XMStoreFloat3(&CamPosition_, vPosition_ + FPup);
    //�J�����̏œ_��player�̖ڐ�ɃZ�b�g
    XMStoreFloat3(&CamTarget_, vPosition_ + vMoveZ_ + FPup);
}

//���_��ݒ肷��֐��F�Œ�ʒu����̒Ǐ]
void Player::CamSet_FIXED()
{
    CamTarget_ = { 15,5,15 };
    //CamPosition_ = { 10,10,-10 };
    CamPosition_ = { 15,50,14 };
    
}


