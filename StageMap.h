#pragma once
#include "Engine/GameObject.h"


class StageMap : public GameObject
{
	//CsvReader CsvMap_[1];
	int Width;//�������i�[
	int Height;//�c�����i�[
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StageMap(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};