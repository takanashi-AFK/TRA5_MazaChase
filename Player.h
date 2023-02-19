#pragma once
#include "Engine/GameObject.h"

enum CAM {
	CAM_FIXED,
	CAM_FPS,
	CAM_MAX,
};

class Player : public GameObject
{
	int hModel_;
	int CamType_;
	Transform PlayerTrans_;

	XMFLOAT3 CamPosition_;
	XMFLOAT3 CamTarget_;

	XMVECTOR vPosition_;
	XMVECTOR vMoveZ_;
	XMVECTOR vMoveX_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//視点を変更する関数
	void CamChange();

	//視点を設定する関数：一人称
	void CamSet_FPS();

	//視点を設定する関数：固定位置からの追従
	void CamSet_FIXED();

	
};