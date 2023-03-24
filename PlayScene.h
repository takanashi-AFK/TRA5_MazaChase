#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

#include "Player.h"
#include "Enemy.h"
#include "StageMap.h"
#include "Timer.h"
#include "MiniMap.h"


class PlayScene : public GameObject
{
public:
	//ステートパターン
	enum {
		S_READY,
		S_PLAY,
		S_GAMEOVER,
	};
	int state_;

private:
	Timer* Time_;
	MiniMap* Map_;
	int ReadyTimer_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//更新：準備
	void UpdateReady();

	//更新：プレイ中
	void UpdatePlay();

	//更新：終了
	void UpdateClear();

	//描画
	void Draw() override;

	//開放
	void Release() override;
};