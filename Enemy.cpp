#include "Enemy.h"

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

	//�����ʒu�̐ݒ�
	{
		EnemyTrans_.position_ = { 3.0f,0.0f,3.0f };
		EnemyTrans_.scale_ = { 0.8f,0.8f,0.8f };
		EnemyTrans_.rotate_.y = 0;
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}

    pStageMap = (StageMap*)FindObject("StageMap");
}

//�X�V
void Enemy::Update()
{
	//player�̈ʒu���擾����
		Player* p = (Player*)FindObject("Player");
		TargetPosition_ = p->GetPosition();

	//Enemy��player�̍����v�Z����
		XMFLOAT3 deltaPosition = XMFLOAT3(
			TargetPosition_.x - EnemyTrans_.position_.x,
			TargetPosition_.y - EnemyTrans_.position_.y,
			TargetPosition_.z - EnemyTrans_.position_.z
		);
	
	//Enemy�̐i�s�������v�Z����
		XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

	//Enemy�̈ړ����x
		float Speed = 0.05;

	//Enemy��Target�Ɍ������Ĉړ�������
		EnemyTrans_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
		EnemyTrans_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
		EnemyTrans_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

	//�x�N�g���̒��������߂�
		XMVECTOR vLength = XMVector3Length(EnemyDir);
		float length = XMVectorGetX(vLength);

		if (length != 0)//vMove�̒�����0����Ȃ��Ƃ�(�����Ă���Ƃ�)
		{
			XMVECTOR vFront = { 0,0,1,0 };//�������̃x�N�g��

			XMVECTOR vDot = XMVector3Dot(vFront, EnemyDir);
			//���̓�̃x�N�g���̓��ς����߂�
			float dot = XMVectorGetX(vDot);
			float angle = acos(dot);//�A�[�N�R�T�C���Ōv�Z�����"�����p�x"�̂ق��̊p�x�����߂�

			XMVECTOR vCross = XMVector3Cross(vFront, EnemyDir);
			//����̃x�N�g���̊O�ς����߂�
			//�O�ς�Y���O��菬����������
			if (XMVectorGetY(vCross) < 0) {
				//angle�� -1 ��������
				angle *= -1;
			}

			EnemyTrans_.rotate_.y = XMConvertToDegrees(angle);
		}

        //�����蔻��̊e���_���\������v�f
        int checkX1, checkZ1;
        int checkX2, checkZ2;

        //�����蔻��̊e����
        #if 0
        {
            //�E���̔���
            {
                //���_�P���\��
                checkX1 = (int)(EnemyTrans_.position_.x + 0.2f);
                checkZ1 = (int)(EnemyTrans_.position_.z + 0.1f);

                //���_�Q���\��
                checkX2 = (int)(EnemyTrans_.position_.x + 0.2f);
                checkZ2 = (int)(EnemyTrans_.position_.z - 0.1f);

                //���_�P,�Q���ǂ��ǂ����𔻒肷��
                if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)) {
                    EnemyTrans_.position_.x = (float)((int)EnemyTrans_.position_.x) + (1.0f - 0.2f);
                }
            }

            //�����̔���
            {
                //���_�P���\��
                checkX1 = (int)(EnemyTrans_.position_.x - 0.2f);
                checkZ1 = (int)(EnemyTrans_.position_.z + 0.1f);

                //���_�Q���\��
                checkX2 = (int)(EnemyTrans_.position_.x - 0.2f);
                checkZ2 = (int)(EnemyTrans_.position_.z - 0.1f);

                //�������ǂ��ǂ����𔻒肷��
                if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)) {
                    EnemyTrans_.position_.x = (float)((int)EnemyTrans_.position_.x) + 0.2f;
                }
            }

            //�����̔���
            {
                //���_�P���\��
                checkX1 = (int)(EnemyTrans_.position_.x + 0.1f);
                checkZ1 = (int)(EnemyTrans_.position_.z + 0.2f);

                //���_�Q���\��
                checkX2 = (int)(EnemyTrans_.position_.x - 0.1f);
                checkZ2 = (int)(EnemyTrans_.position_.z + 0.2f);

                //�������ǂ��ǂ����𔻒肷��
                if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)) {
                    EnemyTrans_.position_.z = (float)((int)EnemyTrans_.position_.z) + (1.0f - 0.2f);
                }
            }

            //�O���̔���
            {
                //���_�P���\��
                checkX1 = (int)(EnemyTrans_.position_.x + 0.1f);
                checkZ1 = (int)(EnemyTrans_.position_.z - 0.2f);

                //���_�Q���\��
                checkX2 = (int)(EnemyTrans_.position_.x - 0.1f);
                checkZ2 = (int)(EnemyTrans_.position_.z - 0.2f);

                //�������ǂ��ǂ����𔻒肷��
                if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)) {
                    EnemyTrans_.position_.z = (float)((int)EnemyTrans_.position_.z) + 0.2f;
                }
            }
        }
        #endif
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
