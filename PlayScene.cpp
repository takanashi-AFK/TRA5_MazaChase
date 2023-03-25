
#include "PlayScene.h"

//一秒間のフレーム処理数
const int FPS = 60;

//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"),Time_(0),ReadyTimer_(0),state_(0)
{
}

//初期化
void PlayScene::Initialize()
{

	Instantiate<Enemy>(this);
	Instantiate<StageMap>(this);
	Instantiate<Player>(this);

	//タイマーの設定
	#if 0
	{
		
		Time_ = Instantiate<Timer>(this);
		Time_->DrawPostion(30, 30);	//描画する位置を指定
		Time_->UseThis(T_TIMER);	//(State_)を使う
		Time_->SetLimit(30);//制限時間を設定(秒)
	}	
	#endif

	//ミニマップの設定
	#if 0
	{
		Map_ = Instantiate<MiniMap>(this);
		Map_->DrawPosition(3, 13);
		Map_->ChengeOpacity(190);
		ReadyTimer_ = (3 * FPS);//(秒 * フレームレート)
	}
	#endif
}

//更新
void PlayScene::Update()
{
	switch (state_)
	{
	case S_READY:		UpdateReady();	break;
	case S_PLAY:		UpdatePlay();	break;
	case S_GAMEOVER:	UpdateClear();	break;
	}
}

//更新：準備
void PlayScene::UpdateReady()
{
	if (ReadyTimer_ > 0) {
		ReadyTimer_--;
		if (ReadyTimer_ == 0) {
			//ステートパターンを変更する
			state_ = S_PLAY;
			//タイマーを開始する
			Time_->TimeStart();
		}
	}
}

//更新：プレイ中
void PlayScene::UpdatePlay()
{
	//if (Time_->IsFinished()) {
	//	//ステートパターンを変更する
	//	state_ = S_GAMEOVER;
	//}
}

//更新：終了
void PlayScene::UpdateClear()
{

}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
