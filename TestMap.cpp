#include "TestMap.h"

#include "Engine/Model.h"
#include "Engine/CsvReader.h"

//コンストラクタ
TestMap::TestMap(GameObject* parent)
	: GameObject(parent, "TestMap"), hModel_{ -1,-1 }, table_(nullptr)
{
	//ZeroMemory(table_, sizeof(table_));//中身をすべて０にする


	//CsvReader型の変数を作り、Load関数を呼び出す。
	CsvReader csv;
	csv.Load("map.csv");//CSVの情報を持ってくる


	//テーブルの配列の大きさを把握
	Width = csv.GetWidth();//CSVの横幅を取得
	Height = csv.GetHeight();//CSVの縦幅を取得

	table_ = new int* [Width];
	for (int x = 0; x < Width; x++)
	{
		table_[x] = new int[Height];
	}

	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++)
			table_[x][z] = csv.GetValue(x, ((Height - 1) - z));
}

//初期化
void TestMap::Initialize()
{
	//ファイルネームを入れる配列
	const char* fileName[] = { "Floor.fbx","Wall.fbx" };

	for (int i = 0; i < TYPE_MAX; i++)
	{
		//モデルデータのロード
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}
}

//更新
void TestMap::Update()
{
}

//描画
void TestMap::Draw()
{
	Transform BlockTrans;//Transform型の変数を作成
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

//開放
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
