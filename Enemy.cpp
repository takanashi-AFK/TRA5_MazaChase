#include "Enemy.h"

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
	{
		EnemyTrans_.position_ = { 3.0f,0.0f,3.0f };
		EnemyTrans_.scale_ = { 0.8f,0.8f,0.8f };
		EnemyTrans_.rotate_.y = 0;
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}

    pStageMap = (StageMap*)FindObject("StageMap");
}

//更新
void Enemy::Update()
{
	//playerの位置を取得する
		Player* p = (Player*)FindObject("Player");
		TargetPosition_ = p->GetPosition();

	//Enemyとplayerの差を計算する
		XMFLOAT3 deltaPosition = XMFLOAT3(
			TargetPosition_.x - EnemyTrans_.position_.x,
			TargetPosition_.y - EnemyTrans_.position_.y,
			TargetPosition_.z - EnemyTrans_.position_.z
		);
	
	//Enemyの進行方向を計算する
		XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

	//Enemyの移動速度
		float Speed = 0.05;

	//EnemyをTargetに向かって移動させる
		EnemyTrans_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
		EnemyTrans_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
		EnemyTrans_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

	//ベクトルの長さを求める
		XMVECTOR vLength = XMVector3Length(EnemyDir);
		float length = XMVectorGetX(vLength);

		if (length != 0)//vMoveの長さが0じゃないとき(動いているとき)
		{
			XMVECTOR vFront = { 0,0,1,0 };//奥向きのベクトル

			XMVECTOR vDot = XMVector3Dot(vFront, EnemyDir);
			//↑の二つのベクトルの内積を求める
			float dot = XMVectorGetX(vDot);
			float angle = acos(dot);//アークコサインで計算すると"狭い角度"のほうの角度を求める

			XMVECTOR vCross = XMVector3Cross(vFront, EnemyDir);
			//↑二つのベクトルの外積を求める
			//外積のYが０より小さかったら
			if (XMVectorGetY(vCross) < 0) {
				//angleに -1 をかける
				angle *= -1;
			}

			EnemyTrans_.rotate_.y = XMConvertToDegrees(angle);
		}

        //あたり判定の各頂点を構成する要素
        int checkX1, checkZ1;
        int checkX2, checkZ2;

        //あたり判定の各処理
        #if 0
        {
            //右側の判定
            {
                //頂点１を構成
                checkX1 = (int)(EnemyTrans_.position_.x + 0.2f);
                checkZ1 = (int)(EnemyTrans_.position_.z + 0.1f);

                //頂点２を構成
                checkX2 = (int)(EnemyTrans_.position_.x + 0.2f);
                checkZ2 = (int)(EnemyTrans_.position_.z - 0.1f);

                //頂点１,２が壁かどうかを判定する
                if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)) {
                    EnemyTrans_.position_.x = (float)((int)EnemyTrans_.position_.x) + (1.0f - 0.2f);
                }
            }

            //左側の判定
            {
                //頂点１を構成
                checkX1 = (int)(EnemyTrans_.position_.x - 0.2f);
                checkZ1 = (int)(EnemyTrans_.position_.z + 0.1f);

                //頂点２を構成
                checkX2 = (int)(EnemyTrans_.position_.x - 0.2f);
                checkZ2 = (int)(EnemyTrans_.position_.z - 0.1f);

                //そこが壁かどうかを判定する
                if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)) {
                    EnemyTrans_.position_.x = (float)((int)EnemyTrans_.position_.x) + 0.2f;
                }
            }

            //奥側の判定
            {
                //頂点１を構成
                checkX1 = (int)(EnemyTrans_.position_.x + 0.1f);
                checkZ1 = (int)(EnemyTrans_.position_.z + 0.2f);

                //頂点２を構成
                checkX2 = (int)(EnemyTrans_.position_.x - 0.1f);
                checkZ2 = (int)(EnemyTrans_.position_.z + 0.2f);

                //そこが壁かどうかを判定する
                if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)) {
                    EnemyTrans_.position_.z = (float)((int)EnemyTrans_.position_.z) + (1.0f - 0.2f);
                }
            }

            //前側の判定
            {
                //頂点１を構成
                checkX1 = (int)(EnemyTrans_.position_.x + 0.1f);
                checkZ1 = (int)(EnemyTrans_.position_.z - 0.2f);

                //頂点２を構成
                checkX2 = (int)(EnemyTrans_.position_.x - 0.1f);
                checkZ2 = (int)(EnemyTrans_.position_.z - 0.2f);

                //そこが壁かどうかを判定する
                if (pStageMap->isWall(checkX1, checkZ1) || pStageMap->isWall(checkX2, checkZ2)) {
                    EnemyTrans_.position_.z = (float)((int)EnemyTrans_.position_.z) + 0.2f;
                }
            }
        }
        #endif
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
