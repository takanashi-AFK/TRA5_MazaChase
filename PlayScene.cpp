#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "StageMap.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<StageMap>(this);
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
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
