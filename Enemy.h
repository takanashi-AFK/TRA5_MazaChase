#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "StageObject.h"

class Enemy : public GameObject
{
	int hModel_;			//モデル番号
	Transform EnemyTrans_;	//enemyのtransformを格納する
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};