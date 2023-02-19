#include "StageObject.h"
#include "Engine/Model.h"

//�R���X�g���N�^
StageObject::StageObject(GameObject* parent)
	: GameObject(parent, "StageObject"),obj_(0)
{
}

//������
void StageObject::Initialize()
{
	//�t�@�C���l�[��������z��
	const char* fileName[] = { "F_Floor.fbx","F_Wall.fbx" };

	for (int i = 0; i < OBJ_MAX; i++)
	{
		//���f���f�[�^�̃��[�h
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}
}

//�X�V
void StageObject::Update()
{
}

//�`��
void StageObject::Draw()
{
	Model::SetTransform(hModel_[obj_], transform_);
	Model::Draw(hModel_[obj_]);
}

//�J��
void StageObject::Release()
{
}