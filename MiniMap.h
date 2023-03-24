#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"

#include "StageObject.h"
#include "StageMap.h"
#include "Player.h"

#include <vector>
using std::vector;


enum {
	MAP_FLOOR,
	MAP_WALL,
	MAP_PLAYER,
	MAP_MAX,
};
class MiniMap:public GameObject
{
private:
	int Width_, Height_;
	float DrawX_, DrawY_;//描画される座標
	int Opacity_;
	float MapSize_;
	Transform MapTrans_;
	Transform PlayerTrans_;

public:
	int hPict_[MAP_MAX];	//モデル番号

	vector<vector<int>> pTable_;
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MiniMap(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//描画位置を設定する関数
	void DrawPosition(float _x, float _y) { this->DrawX_ = _x * 0.01; this->DrawY_ = _y * -0.01; }

	//描画サイズを設定する関数
	//void DrawSize(float _size);

	//不透明度を変更する関数
	void ChengeOpacity(int _Opa) { this->Opacity_ = _Opa; }
};

