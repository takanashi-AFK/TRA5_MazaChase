#include "Enemy.h"
#include "StageObject.h"
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

	//初期位置の設定
	EnemyTrans_.position_ = { 10.0f,0.0f,13.0f };

	Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//更新
void Enemy::Update()
{
//───────────────────────────────────────
//  キャラクターの移動処理
//───────────────────────────────────────

	//レイキャスト(ビーム)を正面から飛ばす
	StageObject* Wall = (StageObject*)FindObject("StageObject");
	int WallModel = Wall->GetModelHandle(OBJ_WALL);

	RayCastData Vision;
	Vision.start = EnemyTrans_.position_;
	Vision.dir = XMFLOAT3(0, 0, 0);//←ここにどこにレイを飛ばすか入れてやる
	Model::RayCast(WallModel, &Vision);

	//壁にぶつかったら右、左、後ろにレイを飛ばす
	RayCastData DoM_Right; //進行方向（Direction of Movement）
	RayCastData DoM_Left; //進行方向（Direction of Movement）
	RayCastData DoM_Back; //進行方向（Direction of Movement）

	//Visionが当たったら
	if (Vision.hit) {
		//配列にするか検討中
		DoM_Right.start = EnemyTrans_.position_;
		DoM_Left.start = EnemyTrans_.position_;
		DoM_Back.start = EnemyTrans_.position_;
		DoM_Left.dir = XMFLOAT3(0, 0, 0);//左に飛ばす
		DoM_Right.dir = XMFLOAT3(0, 0, 0);//右に飛ばす
		DoM_Back.dir = XMFLOAT3(0, 0, 0);//後ろに飛ばす
		Model::RayCast(WallModel, &DoM_Left);
		Model::RayCast(WallModel, &DoM_Right);
		Model::RayCast(WallModel, &DoM_Back);
	}
	else 
	{

	}

	//当たらなかった方に回転し、進む
	//もしどちらとも当たらなかったら、ランダムにして、右、左、後ろに進む
	//playerに当たったら、playerの座標を取得してそこに向かう

//───────────────────────────────────────
//  キャラクターの接触処理
//───────────────────────────────────────

	//playerと接触したとき、playerをキルする
	//この基準
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