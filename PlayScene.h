#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

#include "Player.h"
#include "Enemy.h"
#include "StageMap.h"
#include "Timer.h"
#include "MiniMap.h"


class PlayScene : public GameObject
{
public:
	//�X�e�[�g�p�^�[��
	enum {
		S_READY,
		S_PLAY,
		S_GAMEOVER,
	};
	int state_;

private:
	Timer* Time_;
	MiniMap* Map_;
	int ReadyTimer_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�X�V�F����
	void UpdateReady();

	//�X�V�F�v���C��
	void UpdatePlay();

	//�X�V�F�I��
	void UpdateClear();

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};