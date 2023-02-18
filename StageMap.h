#pragma once
#include "Engine/GameObject.h"


class StageMap : public GameObject
{
	//CsvReader CsvMap_[1];
	int Width;//横幅を格納
	int Height;//縦幅を格納
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
};