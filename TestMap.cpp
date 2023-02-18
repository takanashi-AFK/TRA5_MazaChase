#include "TestMap.h"

#include "Engine/Model.h"
#include "Engine/CsvReader.h"

//�R���X�g���N�^
TestMap::TestMap(GameObject* parent)
	: GameObject(parent, "TestMap"), hModel_{ -1,-1 }, table_(nullptr)
{
	//ZeroMemory(table_, sizeof(table_));//���g�����ׂĂO�ɂ���


	//CsvReader�^�̕ϐ������ALoad�֐����Ăяo���B
	CsvReader csv;
	csv.Load("map.csv");//CSV�̏��������Ă���


	//�e�[�u���̔z��̑傫����c��
	Width = csv.GetWidth();//CSV�̉������擾
	Height = csv.GetHeight();//CSV�̏c�����擾

	table_ = new int* [Width];
	for (int x = 0; x < Width; x++)
	{
		table_[x] = new int[Height];
	}

	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++)
			table_[x][z] = csv.GetValue(x, ((Height - 1) - z));
}

//������
void TestMap::Initialize()
{
	//�t�@�C���l�[��������z��
	const char* fileName[] = { "Floor.fbx","Wall.fbx" };

	for (int i = 0; i < TYPE_MAX; i++)
	{
		//���f���f�[�^�̃��[�h
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}
}

//�X�V
void TestMap::Update()
{
}

//�`��
void TestMap::Draw()
{
	Transform BlockTrans;//Transform�^�̕ϐ����쐬
	for (int x = 0; x < Width; x++)
	{
		for (int z = 0; z < Height; z++)
		{
			BlockTrans.position_.z = z;
			BlockTrans.position_.x = x;

			int Type = table_[x][z];
			Model::SetTransform(hModel_[Type], BlockTrans);
			Model::Draw(hModel_[Type]);
		}
	}
}

//�J��
void TestMap::Release()
{
	for (int x = 0; x < Width; x++)
	{
		delete[] table_[x];
	}
	delete[] table_;
}

bool TestMap::IsWall(int _x, int _z)
{
	return(table_[_x][_z] == TYPE_WALL);
}
