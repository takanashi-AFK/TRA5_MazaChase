#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "StageMap.h"
#include "Engine/Camera.h"

//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<StageMap>(this);
	Instantiate<Player>(this);
	//Instantiate<Enemy>(this);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
