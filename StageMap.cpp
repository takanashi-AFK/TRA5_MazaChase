#include "StageMap.h"
#include "Engine/CsvReader.h"

//�R���X�g���N�^
StageMap::StageMap(GameObject* parent)
	: GameObject(parent, "StageMap")
{
	//CsvMap_[0].Load(".csv");//CSV�̏��������Ă���

	//�e�[�u���̔z��̑傫����c��
	//Width = CsvMap_[1].GetWidth();//CSV�̉������擾
	//Height = CsvMap_[1].GetHeight();//CSV�̏c�����擾
}

//������
void StageMap::Initialize()
{
}

//�X�V
void StageMap::Update()
{
}

//�`��
void StageMap::Draw()
{
}

//�J��
void StageMap::Release()
{
}