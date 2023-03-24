#include "MiniMap.h"

//コンストラクタ
MiniMap::MiniMap(GameObject* parent)
	: GameObject(parent, "MiniMap")
{
	
}

//初期化
void MiniMap::Initialize()
{
	StageMap* pStageMap = (StageMap*)FindObject("StageMap");
	pTable_ = pStageMap->GetTable_();
	Width_ = pStageMap->GetWidth();
	Height_ = pStageMap->GetHeight();
	const char* fileName[] = { "P_MapWall.png","P_MapFloor.png","P_MapPlayer.png" };

	for (int i = 0; i < MAP_MAX; i++)
	{
		//モデルデータのロード
		hPict_[i] = Image::Load(fileName[i]);
		assert(hPict_[i] >= 0);
	}

	MapSize_ = 0.015f;
	MapTrans_.scale_ = { MapSize_,MapSize_,1 };
	PlayerTrans_.scale_ = { MapSize_,MapSize_,1 };

}

//更新
void MiniMap::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	PlayerTrans_.position_.x = (pPlayer->GetPosition().x * 0.03f) - 0.98f;
	//PlayerTrans_.position_.x = ((pPlayer->GetPosition().x - 2.04f) * 0.0125f) - 0.97f;

	PlayerTrans_.position_.y = (pPlayer->GetPosition().z * 0.053f) + 0.22f;

}

//描画
void MiniMap::Draw()
{
	for (float x = 0; x < Width_; x++)
		for (float y = 0; y < Height_; y++) {

			MapTrans_.position_.x = (x * 0.03f) + (DrawX_ - 0.98f);
			MapTrans_.position_.y = (y * 0.053f) +(DrawY_ + 0.22f);

			int Type = pTable_[x][y];

			Image::SetTransform(hPict_[Type], MapTrans_);
			Image::Draw(hPict_[Type]);
			Image::SetAlpha(hPict_[Type], Opacity_);
		}

	Image::SetTransform(hPict_[MAP_PLAYER], PlayerTrans_);
	Image::Draw(hPict_[MAP_PLAYER]);
}

//開放
void MiniMap::Release()
{
}

