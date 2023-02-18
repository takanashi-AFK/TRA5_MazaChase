#pragma once
#include "Engine/GameObject.h"

enum
{
	TYPE_FLOOR,
	TYPE_WALL,
	TYPE_MAX,
};
//テストシーンを管理するクラス
class TestMap : public GameObject
{
private:

	int hModel_[TYPE_MAX];
	int Width;//横幅を格納
	int Height;//縦幅を格納
	int** table_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestMap(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//指定した位置が通れるのか通れないかを調べる関数
	//引数：_x,_y	 調べる位置
	//戻値：通れる = true/通れない = false
	bool IsWall(int _x, int _z);

};