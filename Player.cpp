#include "Player.h"

//コンストラクタ
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), PlayerTrans_(transform_),CamType_(0),moving_(0)
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("F_Player(move).fbx");
    assert(hModel_ >= 0);

    HRFrame_ = Image::Load("P_hFrame2.png");
    assert(HRFrame_ >= 0);

    //初期位置の設定
    PlayerTrans_.position_ = { 10.0f,0.0f,10.0f };

    //アニメーション動作処理
    Model::SetAnimFrame(hModel_, 0, 60, 1);

    pStageMap = (StageMap*)FindObject("StageMap");
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

        //移動速度
        float Speed = 0.05f;
        if (Input::IsKey(DIK_LSHIFT)) { Speed = 0.1f; }

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

        //カメラを変更する
        if (Input::IsKeyDown(DIK_F4)) { CamChange(); }

//───────────────────────────────────────
//  カメラの移動処理
//───────────────────────────────────────

    switch (CamType_)
    {
    case CAM_FIXED:	CamSet_FIXED();	break;
    case CAM_FPS:	CamSet_FPS();	break;
    }

    Camera::SetPosition(CamPosition_);
    Camera::SetTarget(CamTarget_);
        
    //あたり判定の各頂点を構成する要素
    int CheckX1, CheckZ1;
    int CheckX2, CheckZ2;

    //デバック用
    //Playerが壁と接触しているかを確認する
    if (pStageMap->isWall(PlayerTrans_.position_.x, PlayerTrans_.position_.z)){
        Debug::Log("〇",true);}
    else{
        Debug::Log("△", true);}


    //あたり判定の各処理
    #if 0
    {
        //右側の判定
        {
            //頂点１を構成
            CheckX1 = (int)(PlayerTrans_.position_.x + 1.0f);
            CheckZ1 = (int)(PlayerTrans_.position_.z - 1.0f);

            //頂点２を構成
            CheckX2 = (int)(PlayerTrans_.position_.x + 1.0f);
            CheckZ2 = (int)(PlayerTrans_.position_.z + 1.0f);

            //そこが壁かどうかを判定する
            if (pStageMap->isWall(CheckX1, CheckZ1) || pStageMap->isWall(CheckX2, CheckZ2))//引数：playerの位置
            {
                PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + (0.8f - 0.4f);
            }
        }

        //左側の判定
        {
            //頂点１を構成
            CheckX1 = (int)(PlayerTrans_.position_.x - 1.0f);
            CheckZ1 = (int)(PlayerTrans_.position_.z - 1.0f);

            //頂点２を構成
            CheckX2 = (int)(PlayerTrans_.position_.x - 1.0f);
            CheckZ2 = (int)(PlayerTrans_.position_.z + 1.0f);

            //そこが壁かどうかを判定する
            if (pStageMap->isWall(CheckX1, CheckZ1) || pStageMap->isWall(CheckX2, CheckZ2))//引数：playerの位置
            {
                PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + 0.4f;
            }
        }

        //奥側の判定
        {
            //頂点１を構成
            CheckX1 = (int)(PlayerTrans_.position_.x + 1.0f);
            CheckZ1 = (int)(PlayerTrans_.position_.z - 1.0f);

            //頂点２を構成
            CheckX2 = (int)(PlayerTrans_.position_.x - 1.0f);
            CheckZ2 = (int)(PlayerTrans_.position_.z - 1.0f);

            //そこが壁かどうかを判定する
            if (pStageMap->isWall(CheckX1, CheckZ1) || pStageMap->isWall(CheckX2, CheckZ2))//引数：playerの位置
            {
                PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + (0.8f - 0.4f);
            }
        }

        //前側の判定
        {
            //頂点１を構成
            CheckX1 = (int)(PlayerTrans_.position_.x + 1.0f);
            CheckZ1 = (int)(PlayerTrans_.position_.z + 1.0f);

            //頂点２を構成
            CheckX2 = (int)(PlayerTrans_.position_.x - 1.0f);
            CheckZ2 = (int)(PlayerTrans_.position_.z + 1.0f);

            //そこが壁かどうかを判定する
            if (pStageMap->isWall(CheckX1, CheckZ1) || pStageMap->isWall(CheckX2, CheckZ2))//引数：playerの位置
            {
                PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + 0.4;
            }
        }
    }
    #endif

}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, PlayerTrans_);
    Model::Draw(hModel_);

    /*Image::SetTransform(HRFrame_, transform_);
    Image::Draw(HRFrame_);*/
}

//開放
void Player::Release()
{
}

//Playerの現在地を取得する関数
XMFLOAT3 Player::GetPosition()
{
    return(this->PlayerTrans_.position_);
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
    XMVECTOR FPup = { 0.0f,1.2f,0.0f };
    XMStoreFloat3(&CamPosition_, vPosition_ + FPup);
    //カメラの焦点をplayerの目先にセット
    XMStoreFloat3(&CamTarget_, vPosition_ + vMoveZ_ + FPup);
}

//視点を設定する関数：固定位置からの追従
void Player::CamSet_FIXED()
{
    CamTarget_ = { 15,5,15 };
    //CamPosition_ = { 10,10,-10 };
    CamPosition_ = { 15,50,14 };
    
}


