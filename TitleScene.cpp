#include "TitleScene.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),hPict_(-1),Opacity_(0),SceneMove_(false)
{
}

//������
void TitleScene::Initialize()
{
	/*hPict_ = Image::Load("P_Fadeout.png");
	assert(hPict_ >= 0);*/
}

//�X�V
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

//�`��
void TitleScene::Draw()
{
	/*Image::SetAlpha(hPict_, Opacity_);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);*/
}

//�J��
void TitleScene::Release()
{
}
