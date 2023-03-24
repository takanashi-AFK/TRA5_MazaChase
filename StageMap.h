#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

#include "StageObject.h"

#include <vector>
using std::vector;

class StageMap : public GameObject
{
	CsvReader CsvMap_;	//CSV�f�[�^���i�[
	int Width;			//CSV����ǂݎ�����������i�[
	int Height;			//CSV����ǂݎ�����c�����i�[
	vector<vector<int>> Table_;//�X�e�[�W�����i�[����񎟌��z��

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

	//Table.size & data�𑼏��ɓn���֐�
	vector<vector<int>>& GetTable_() { return(this->Table_);}
	
	//Table.Width��n���֐�
	int GetWidth() { return (this->Width); }

	//Table.Height��n���֐�
	int GetHeight() { return (this->Height); }

	//�ǂ��ǂ������m�F����֐�
	bool isWall(int _x, int _z);
};