#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

class StageMap : public GameObject
{
	CsvReader CsvMap_;	//CSV�f�[�^���i�[
	int Width;			//CSV����ǂݎ�����������i�[
	int Height;			//CSV����ǂݎ�����c�����i�[
	int** table_;		//�X�e�[�W�����i�[
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