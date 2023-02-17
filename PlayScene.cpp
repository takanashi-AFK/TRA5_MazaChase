#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine/Camera.h"

//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Player>(this);

	CamTarget_ = { 0,1.5,0 };
	CamPosition_ = { 0,1.5,-5 };
	Camera::SetTarget(CamTarget_);
	Camera::SetPosition(CamPosition_);

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
