#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "StageMap.h"
#include "Player.h"

class Enemy : public GameObject
{
	int hModel_;			//���f���ԍ�
	Transform EnemyTrans_;	//enemy��transform���i�[����
	XMFLOAT3 TargetPosition_;

	StageMap* pStageMap;	//�|�C���^�ϐ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Enemy(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};