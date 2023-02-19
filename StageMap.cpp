#include "StageMap.h"
#include "StageObject.h"


//コンストラクタ
StageMap::StageMap(GameObject* parent)
	: GameObject(parent, "StageMap")
{
//───────────────────────────────────────
//  CSVデータの初期化
//───────────────────────────────────────
	//CSVデータをロードする
	//for (int i = 0; i < CSVMAX; i++){
		CsvMap_.Load("Map.csv");
	
	
	//テーブルの配列の大きさを把握
	Width = CsvMap_.GetWidth();//CSVの横幅を取得
	Height = CsvMap_.GetHeight();//CSVの縦幅を取得

	table_ = new int* [Width];
	for (int x = 0; x < Width; x++){
		table_[x] = new int[Height];
	}

	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++)
			table_[x][z] = CsvMap_.GetValue(x, ((Height - 1) - z));
}

//初期化
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

//更新
void StageMap::Update()
{
}

//描画
void StageMap::Draw()
{
	
}

//開放
void StageMap::Release()
{
}