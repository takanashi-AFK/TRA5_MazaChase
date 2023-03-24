#include "TitleScene.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),hPict_(-1),Opacity_(0),SceneMove_(false)
{
}

//初期化
void TitleScene::Initialize()
{
	/*hPict_ = Image::Load("P_Fadeout.png");
	assert(hPict_ >= 0);*/
}

//更新
void TitleScene::Update()
{
	/*if (Input::IsKeyDown(DIK_SPACE)){
		SceneMove_ = true;
	}

	if(SceneMove_)Opacity_++;
	if (Opacity_ >= 255) {
		SceneManager* Clear = (SceneManager*)FindObject("SceneManager");
		Clear->ChangeScene(SCENE_ID_PLAY);
	}*/
}

//描画
void TitleScene::Draw()
{
	/*Image::SetAlpha(hPict_, Opacity_);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);*/
}

//開放
void TitleScene::Release()
{
}
