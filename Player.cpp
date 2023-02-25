#include "Player.h"

//コンストラクタ
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), PlayerTrans_(transform_),CamType_(0)
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("F_Player(move).fbx");
    assert(hModel_ >= 0);

    //初期位置の設定
    PlayerTrans_.position_ = { 10.0f,0.0f,10.0f };

    //アニメーション動作処理
    Model::SetAnimFrame(hModel_, 0, 60, 1);
}

//更新
void Player::Update()
{
//───────────────────────────────────────
//  キャラクターの移動処理
//───────────────────────────────────────

    /*＝＝＝向いている方向の操作・更新＝＝＝*/


    //マウスの移動量を取得
    XMFLOAT3 MouseMove_ = Input::GetMouseMove();
    PlayerTrans_.rotate_.y += (MouseMove_.x / 10.0f);

    /*＝＝＝＝ 前後左右の移動・更新 ＝＝＝＝*/

    //向いている方向を取得

    //原点の位置とPlayerの位置二つを結んだベクトルを作成
    vPosition_ = XMLoadFloat3(&PlayerTrans_.position_);

    float Speed = 0.1f;
    //原点からZに垂直なベクトルを作成
    vMoveZ_ = { 0.0f,0.0f,Speed,0.0f };//{x,y,z,0}

    //原点からXに垂直なベクトルを作成
    vMoveX_ = { Speed,0.0f,0.0f,0.0f };//{x,y,z,0}

    //transform_.rotate_.y度回転させる行列を作成
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(PlayerTrans_.rotate_.y));

    // vMoveZ / vMoveX をRotateMatYで回転させる
    vMoveZ_ = XMVector3TransformCoord(vMoveZ_, RotateMatY);
    vMoveX_ = XMVector3TransformCoord(vMoveX_, RotateMatY);

    //「W」キー：前に進む
    if (Input::IsKey(DIK_W)) {
        vPosition_ += vMoveZ_;
        XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
    }

    //「S」キー：後ろに進む
    if (Input::IsKey(DIK_S)) {
        vPosition_ -= vMoveZ_;
        XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
    }

    //「A」キー：左に進む
    if (Input::IsKey(DIK_A)) {
        vPosition_ -= vMoveX_;
        XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
    }

    //「D」キー：右に進む
    if (Input::IsKey(DIK_D)) {
        vPosition_ += vMoveX_;
        XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
    }

//───────────────────────────────────────
//  カメラの移動処理
//───────────────────────────────────────

    //カメラを変更する
    if (Input::IsKeyDown(DIK_F4)) { CamChange(); }

    switch (CamType_)
    {
    case CAM_FIXED:	CamSet_FIXED();	break;
    case CAM_FPS:	CamSet_FPS();	break;
    }

    Camera::SetPosition(CamPosition_);
    Camera::SetTarget(CamTarget_);
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

//視点を変更する関数
void Player::CamChange()
{
    if (CamType_ < (CAM_MAX - 1))
        CamType_++;
    else
        CamType_ = 0;
}

//視点を設定する関数：一人称
void Player::CamSet_FPS()
{
    //カメラの位置をplayerの位置にセット
    XMVECTOR FPup = { 0.0f,1.0f,0.0f };
    XMStoreFloat3(&CamPosition_, vPosition_ + FPup);
    //カメラの焦点をplayerの目先にセット
    XMStoreFloat3(&CamTarget_, vPosition_ + vMoveZ_ + FPup);
}

//視点を設定する関数：固定位置からの追従
void Player::CamSet_FIXED()
{
    CamTarget_ = {PlayerTrans_.position_};
    CamPosition_ = { 10,10,-10 };
}
