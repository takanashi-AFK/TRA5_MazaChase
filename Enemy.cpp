#include "Enemy.h"

#include "Engine/Input.h"
#include "Engine/Model.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1), EnemyTrans_(transform_)
{
}

//初期化
void Enemy::Initialize()
{
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//更新
void Enemy::Update()
{
//───────────────────────────────────────
//  キャラクターの移動処理
//───────────────────────────────────────
}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, EnemyTrans_);
	Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
}