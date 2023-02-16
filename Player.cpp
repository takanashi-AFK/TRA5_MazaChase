#include "Player.h"

#include "Engine/Input.h"
#include "Engine/Model.h"

//コンストラクタ
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), PlayerTrans_(transform_)
{
}

//初期化
void Player::Initialize()
{
    hModel_ = Model::Load("F_Player(move).fbx");
    assert(hModel_ >= 0);

    Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//更新
void Player::Update()
{
//───────────────────────────────────────
//  キャラクターの移動処理
//───────────────────────────────────────

    /*＝＝＝向いている方向の操作・更新＝＝＝*/
     //「←」キー：左方向に回転
    if (Input::IsKey(DIK_LEFT)) {
        PlayerTrans_.rotate_.y -= 2.0f;
    }
    //「→」キー：右方向に回転
    if (Input::IsKey(DIK_RIGHT)) {
        PlayerTrans_.rotate_.y += 2.0f;
    }

    /*＝＝＝＝ 前後左右の移動・更新 ＝＝＝＝*/

    //向いている方向を取得

    //原点の位置とPlayerの位置二つを結んだベクトルを作成
    XMVECTOR vPosition = XMLoadFloat3(&PlayerTrans_.position_);

    //原点からZに垂直なベクトルを作成
    XMVECTOR vMoveZ = { 0.0f,0.0f,0.05f,0.0f };//{x,y,z,0}

    //原点からXに垂直なベクトルを作成
    XMVECTOR vMoveX = { 0.05f,0.0f,0.0f,0.0f };//{x,y,z,0}

    //transform_.rotate_.y度回転させる行列を作成
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(PlayerTrans_.rotate_.y));

    // vMoveZ / vMoveX をRotateMatYで回転させる
    vMoveZ = XMVector3TransformCoord(vMoveZ, RotateMatY);
    vMoveX = XMVector3TransformCoord(vMoveX, RotateMatY);

    //「W」キー：前に進む
    if (Input::IsKey(DIK_W)) {
        vPosition += vMoveZ;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&PlayerTrans_.position_, vPosition);
    }

    //「S」キー：後ろに進む
    if (Input::IsKey(DIK_S)) {
        vPosition -= vMoveZ;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&PlayerTrans_.position_, vPosition);
    }

    //「A」キー：左に進む
    if (Input::IsKey(DIK_A)) {
        vPosition -= vMoveX;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&PlayerTrans_.position_, vPosition);
    }

    //「D」キー：右に進む
    if (Input::IsKey(DIK_D)) {
        vPosition += vMoveX;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&PlayerTrans_.position_, vPosition);
    }
}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, PlayerTrans_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}
