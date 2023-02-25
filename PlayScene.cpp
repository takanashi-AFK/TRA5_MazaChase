
#include "PlayScene.h"

//一秒間のフレーム処理数
const int FPS = 60;

//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"),Time_(0),ReadyTimer_(0)
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<StageMap>(this);
	Instantiate<Player>(this);
	//Instantiate<Enemy>(this);

	Time_ = Instantiate<Timer>(this);
	Time_->DrawPostion(30, 30);	//描画する位置を指定
	Time_->UseThis(T_TIMER);//(State_)を使う
	Time_->SetLimit(6);			//制限時間を設定(秒)
	ReadyTimer_ = (3 * FPS);//(秒 * フレームレート)
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
	//playerを動ける状態にする
	Player* P = (Player*)FindObject("Player");
	P->SetMove(true);

	if (Time_->IsFinished()) {
		//ステートパターンを変更する
		state_ = S_GAMEOVER;
	}
}

//更新：終了
void PlayScene::UpdateClear()
{
	SceneManager* Clear = (SceneManager*)FindObject("SceneManager");
	Clear->ChangeScene(SCENE_ID_CLEAR);
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
