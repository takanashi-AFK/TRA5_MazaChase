#include "Enemy.h"
#include "StageObject.h"
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

	//�����ʒu�̐ݒ�
	EnemyTrans_.position_ = { 10.0f,0.0f,13.0f };

	Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//�X�V
void Enemy::Update()
{
//������������������������������������������������������������������������������
//  �L�����N�^�[�̈ړ�����
//������������������������������������������������������������������������������

	//���C�L���X�g(�r�[��)�𐳖ʂ����΂�
	StageObject* Wall = (StageObject*)FindObject("StageObject");
	int WallModel = Wall->GetModelHandle(OBJ_WALL);

	RayCastData Vision;
	Vision.start = EnemyTrans_.position_;
	Vision.dir = XMFLOAT3(0, 0, 0);//�������ɂǂ��Ƀ��C���΂�������Ă��
	Model::RayCast(WallModel, &Vision);

	//�ǂɂԂ�������E�A���A���Ƀ��C���΂�
	RayCastData DoM_Right; //�i�s�����iDirection of Movement�j
	RayCastData DoM_Left; //�i�s�����iDirection of Movement�j
	RayCastData DoM_Back; //�i�s�����iDirection of Movement�j

	//Vision������������
	if (Vision.hit) {
		//�z��ɂ��邩������
		DoM_Right.start = EnemyTrans_.position_;
		DoM_Left.start = EnemyTrans_.position_;
		DoM_Back.start = EnemyTrans_.position_;
		DoM_Left.dir = XMFLOAT3(0, 0, 0);//���ɔ�΂�
		DoM_Right.dir = XMFLOAT3(0, 0, 0);//�E�ɔ�΂�
		DoM_Back.dir = XMFLOAT3(0, 0, 0);//���ɔ�΂�
		Model::RayCast(WallModel, &DoM_Left);
		Model::RayCast(WallModel, &DoM_Right);
		Model::RayCast(WallModel, &DoM_Back);
	}
	else 
	{

	}

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