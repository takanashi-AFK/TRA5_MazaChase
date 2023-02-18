#pragma once
#include "Engine/GameObject.h"


class Player : public GameObject
{
	int hModel_;
	Transform PlayerTrans_;

	XMFLOAT3 CamPosition_;
	XMFLOAT3 CamTarget_;
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
};

//�����ƃv�b�V������ĂȂ��́H