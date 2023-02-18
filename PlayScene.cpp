#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "TestMap.h"
#include "Engine/Camera.h"

//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<TestMap>(this);
	Instantiate<Player>(this);

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
