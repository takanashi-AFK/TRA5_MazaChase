#include "PlayScene.h"
#include "Enemy.h"

#include "Engine/Camera.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Enemy>(this);

	CamTarget_ = { 0,1.5,0 };
	CamPosition_ = { 0,1.5,-5 };
	Camera::SetTarget(CamTarget_);
	Camera::SetPosition(CamPosition_);

}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}
