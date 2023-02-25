#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "Engine/VFX.h"

enum {
	CAM_FIXED,
	CAM_FPS,
	CAM_MAX,
};

class Player : public GameObject
{
	int hModel_;	//���f���ԍ�
	int CamType_;	//�J�����ԍ�
	bool moving_;
	
	Transform	PlayerTrans_;	//player��transform���i�[����

	XMFLOAT3	CamPosition_;	//�J�����̈ʒu���i�[����
	XMFLOAT3	CamTarget_;		//�J�����̏œ_���i�[����

	XMVECTOR	vPosition_;		//player��position��vector�^�Ƃ��Ċi�[����
	XMVECTOR	vMoveZ_;		//������i�y���j
	XMVECTOR	vMoveX_;		//������i�w���j
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�ړ�����������֐�
	void PlayerMove();

	//���_��ύX����֐�
	void CamChange();

	//���_��ݒ肷��֐��F��l��
	void CamSet_FPS();

	//���_��ݒ肷��֐��F�Œ�ʒu����̒Ǐ]
	void CamSet_FIXED();

	//player�̏�Ԃ�ݒ肷��֐�
	void SetMove(bool _move);

	//player�������邩�ǂ�����Ԃ��֐�
	bool isMove() { return(moving_); }

};