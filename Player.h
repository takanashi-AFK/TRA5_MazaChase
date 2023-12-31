#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "Engine/VFX.h"

#include "StageMap.h"


enum {
	CAM_FIXED,
	CAM_FPS,
	CAM_MAX,
};

class Player : public GameObject
{
	int hModel_;	//モデル番号
	int CamType_;	//カメラ番号
	bool moving_;

	int HRFrame_;
	
	Transform	PlayerTrans_;	//playerのtransformを格納する

	XMFLOAT3	CamPosition_;	//カメラの位置を格納する
	XMFLOAT3	CamTarget_;		//カメラの焦点を格納する

	XMVECTOR	vPosition_;		//playerのpositionをvector型として格納する
	XMVECTOR	vMoveZ_;		//空方向（Ｚ軸）
	XMVECTOR	vMoveX_;		//空方向（Ｘ軸）

	StageMap* pStageMap;	//ポインタ変数
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

	//playerの現在地を取得する関数
	XMFLOAT3 GetPosition();

	//視点を変更する関数
	void CamChange();

	//視点を設定する関数：一人称
	void CamSet_FPS();

	//視点を設定する関数：固定位置からの追従
	void CamSet_FIXED();

};