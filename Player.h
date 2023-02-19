#pragma once
#include "Engine/GameObject.h"

enum CAM {
	CAM_FIXED,
	CAM_FPS,
	CAM_MAX,
};

class Player : public GameObject
{
	int hModel_;
	int CamType_;
	Transform PlayerTrans_;

	XMFLOAT3 CamPosition_;
	XMFLOAT3 CamTarget_;

	XMVECTOR vPosition_;
	XMVECTOR vMoveZ_;
	XMVECTOR vMoveX_;
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

	//���_��ύX����֐�
	void CamChange();

	//���_��ݒ肷��֐��F��l��
	void CamSet_FPS();

	//���_��ݒ肷��֐��F�Œ�ʒu����̒Ǐ]
	void CamSet_FIXED();

	
};