#include "StageMap.h"
#include "Engine/CsvReader.h"

//コンストラクタ
StageMap::StageMap(GameObject* parent)
	: GameObject(parent, "StageMap")
{
	//CsvMap_[0].Load(".csv");//CSVの情報を持ってくる

	//テーブルの配列の大きさを把握
	//Width = CsvMap_[1].GetWidth();//CSVの横幅を取得
	//Height = CsvMap_[1].GetHeight();//CSVの縦幅を取得
}

//初期化
void StageMap::Initialize()
{
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