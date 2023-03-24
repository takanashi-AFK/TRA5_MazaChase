#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

#include "StageObject.h"

#include <vector>
using std::vector;

class StageMap : public GameObject
{
	CsvReader CsvMap_;	//CSVデータを格納
	int Width;			//CSVから読み取った横幅を格納
	int Height;			//CSVから読み取った縦幅を格納
	vector<vector<int>> Table_;//ステージ情報を格納する二次元配列

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StageMap(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//Table.size & dataを他所に渡す関数
	vector<vector<int>>& GetTable_() { return(this->Table_);}
	
	//Table.Widthを渡す関数
	int GetWidth() { return (this->Width); }

	//Table.Heightを渡す関数
	int GetHeight() { return (this->Height); }

	//壁かどうかを確認する関数
	bool isWall(int _x, int _z);
};