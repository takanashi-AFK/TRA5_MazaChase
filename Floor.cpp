#include "Floor.h"
#include "Engine/Model.h"

//コンストラクタ
Floor::Floor(GameObject* parent)
	: GameObject(parent, "Floor"), hModel_(-1)
{
}

//初期化
void Floor::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("F_Floor.fbx");
	assert(hModel_ >= 0);
}

//更新
void Floor::Update()
{
}

//描画
void Floor::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Floor::Release()
{
}