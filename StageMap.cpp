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

	//配列をWidth×Heightで初期化
	Table_.resize(Width, vector<int>(Height, 0));

	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++)
			Table_[x][z] = CsvMap_.GetValue(x, ((Height - 1) - z));
}

//初期化
void StageMap::Initialize()
{
	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++) {
			if (Table_[x][z] == 0) {
				StageObject* FLOOR = Instantiate<StageObject>(GetParent());
				FLOOR->ObjectSet(OBJ_FLOOR);
				FLOOR->SetPosition(XMFLOAT3(x*2, 0, z*2));
			}
			else if (Table_[x][z] == 1) {
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

/*
2023/02/20～
なぜか重くなるため解決策思考中
多分原因はInstantateのしすぎ
実体の数が多すぎるのかな

だから、WallやFloorなどのステージ構成オブジェクトは描画で
書くべきなのかな。。でもステージマップクラス作るならその中で完結させたいよね

2023/02/21～
重くなる状態を花井社長によるGameObject.cppの改変により解決

2023/02/23～
配列をダブルポインタによる作成から、vector型での作成に変更

	int** table_;		//ステージ情報を格納

	table_ = new int* [Width];
		for (int x = 0; x < Width; x++){
			table_[x] = new int[Height];
		}

	newで作ったものは消す！
	for (int x = 0; x < Width; x++)
	{
		delete[] table_[x];
	}
	delete[] table_;
*/