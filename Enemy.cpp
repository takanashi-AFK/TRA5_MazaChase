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
	hModel_ = Model::Load("F_Player(move).fbx");
	assert(hModel_ >= 0);

	Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//更新
void Enemy::Update()
{
//───────────────────────────────────────
//  キャラクターの移動処理
//───────────────────────────────────────

    /*＝＝＝向いている方向の操作・更新＝＝＝*/
    RotateRight();  //「→」キー：右方向に回転
    RotateLeft();   //「←」キー：左方向に回転

    /*＝＝＝＝ 前後左右の移動・更新 ＝＝＝＝*/

    //向いている方向を取得

    //原点の位置とEnemyの位置二つを結んだベクトルを作成
    XMVECTOR vPosition = XMLoadFloat3(&EnemyTrans_.position_);

    //原点からZに垂直なベクトルを作成
    XMVECTOR vMoveZ = { 0.0f,0.0f,0.05f,0.0f };//{x,y,z,0}

    //原点からXに垂直なベクトルを作成
    XMVECTOR vMoveX = { 0.05f,0.0f,0.0f,0.0f };//{x,y,z,0}

    //transform_.rotate_.y度回転させる行列を作成
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(EnemyTrans_.rotate_.y));

    // vMoveZ / vMoveX をRotateMatYで回転させる
    vMoveZ = XMVector3TransformCoord(vMoveZ, RotateMatY);
    vMoveX = XMVector3TransformCoord(vMoveX, RotateMatY);

    //「W」キー：前に進む
    if (Input::IsKey(DIK_W)) {
        vPosition += vMoveZ;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&EnemyTrans_.position_, vPosition);
    }

    //「S」キー：後ろに進む
    if (Input::IsKey(DIK_S)) {
        vPosition -= vMoveZ;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&EnemyTrans_.position_, vPosition);
    }

    //「A」キー：左に進む
    if (Input::IsKey(DIK_A)) {
        vPosition -= vMoveX;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&EnemyTrans_.position_, vPosition);
    }

    //「D」キー：右に進む
    if (Input::IsKey(DIK_D)) {
        vPosition += vMoveX;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&EnemyTrans_.position_, vPosition);
    }
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

void Enemy::RotateRight()
{
    if (Input::IsKey(DIK_RIGHT)) {
        EnemyTrans_.rotate_.y += 2.0f;
    }
}

void Enemy::RotateLeft()
{
    if (Input::IsKey(DIK_LEFT)) {
        EnemyTrans_.rotate_.y -= 2.0f;
    }
}

/*
float Speed = 0.01f;
//移動：右
if (Input::IsKey(DIK_D))
{
    transform_.position_.x += Speed;
    transform_.rotate_.y = 90.0f;
}

//移動：左
if (Input::IsKey(DIK_A))
{
    transform_.position_.x -= Speed;
    transform_.rotate_.y = -90.0f;
}

//移動：奥
if (Input::IsKey(DIK_W))
{
    transform_.position_.z += Speed;
    transform_.rotate_.y = 0.0f;
}

//移動：手前
if (Input::IsKey(DIK_S))
{
    transform_.position_.z -= Speed;
    transform_.rotate_.y = -180.0f;
}
*/

////「→」キーを押すと右回転
//if (Input::IsKey(DIK_RIGHT))
//{
//    transform_.rotate_.y += 2.0f;
//}
////「←」キーを押すと左回転
//if (Input::IsKey(DIK_LEFT))
//{
//    transform_.rotate_.y -= 2.0f;
//}
//
////現在地をベクトル型に変換
//XMVECTOR VectorPos = XMLoadFloat3(&transform_.position_);
////１フレームの移動ベクトル
//XMVECTOR VectorMove = { 0.0f,0.0f,0.10f,0.0f };
////transform_.rotate_.y度回転させる行列を作成
//XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
//XMMATRIX RotateMatYL = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y - 90));
//
//
////「W」キーを押すと向いている方向に進む
//if (Input::IsKey(DIK_W))
//{
//    //移動ベクトルを変形(同じ向きに回転)
//    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatY);
//    //向いている方向に進む処理
//    //移動
//    VectorPos += (VectorMove);
//    //現在地をベクトルからいつものtransform.position_にもどす
//    XMStoreFloat3(&transform_.position_, VectorPos);
//}
//
////「S」キーを押すと向いている方向の後ろに進む
//if (Input::IsKey(DIK_S))
//{
//    //移動ベクトルを変形(同じ向きに回転)
//    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatY);
//    //移動
//    VectorPos -= VectorMove;
//    //現在地をベクトルからいつものtransform.position_にもどす
//    XMStoreFloat3(&transform_.position_, VectorPos);
//}
//
////「A」キーを押すと向いている方向の左に進む
//if (Input::IsKey(DIK_A))
//{
//    //移動ベクトルを変形(同じ向きに回転)
//    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatYL);
//    //移動
//    VectorPos += VectorMove;
//    //現在地をベクトルからいつものtransform.position_にもどす
//    XMStoreFloat3(&transform_.position_, VectorPos);
//}
//
////「D」キーを押すと向いている方向の右に進む
//if (Input::IsKey(DIK_A))
//{
//    //移動ベクトルを変形(同じ向きに回転)
//    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatYL);
//    //移動
//    VectorPos -= VectorMove;
//    //現在地をベクトルからいつものtransform.position_にもどす
//    XMStoreFloat3(&transform_.position_, VectorPos);
//}
////□＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝□