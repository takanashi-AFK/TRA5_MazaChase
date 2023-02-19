#include "StageMap.h"
#include "StageObject.h"


//�R���X�g���N�^
StageMap::StageMap(GameObject* parent)
	: GameObject(parent, "StageMap")
{
//������������������������������������������������������������������������������
//  CSV�f�[�^�̏�����
//������������������������������������������������������������������������������
	//CSV�f�[�^�����[�h����
	//for (int i = 0; i < CSVMAX; i++){
		CsvMap_.Load("Map.csv");
	
	
	//�e�[�u���̔z��̑傫����c��
	Width = CsvMap_.GetWidth();//CSV�̉������擾
	Height = CsvMap_.GetHeight();//CSV�̏c�����擾

	table_ = new int* [Width];
	for (int x = 0; x < Width; x++){
		table_[x] = new int[Height];
	}

	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++)
			table_[x][z] = CsvMap_.GetValue(x, ((Height - 1) - z));
}

//������
void StageMap::Initialize()
{
	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++) {
			if (table_[x][z] == 0) {
				StageObject* FLOOR = Instantiate<StageObject>(GetParent());
				FLOOR->ObjectSet(OBJ_FLOOR);
				FLOOR->SetPosition(XMFLOAT3(x*2, 0, z*2));
			}
			else if (table_[x][z] == 1) {
				StageObject* WALL = Instantiate<StageObject>(GetParent());
				WALL->ObjectSet(OBJ_WALL);
				WALL->SetPosition(XMFLOAT3(x*2, 0, z*2));
			}
		}
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