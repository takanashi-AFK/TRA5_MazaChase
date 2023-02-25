
#include "PlayScene.h"

//��b�Ԃ̃t���[��������
const int FPS = 60;

//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"),Time_(0),ReadyTimer_(0)
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<StageMap>(this);
	Instantiate<Player>(this);
	//Instantiate<Enemy>(this);

	Time_ = Instantiate<Timer>(this);
	Time_->DrawPostion(30, 30);	//�`�悷��ʒu���w��
	Time_->UseThis(T_TIMER);//(State_)���g��
	Time_->SetLimit(60);			//�������Ԃ�ݒ�(�b)
	ReadyTimer_ = (3 * FPS);//(�b * �t���[�����[�g)
}

//�X�V
void PlayScene::Update()
{
	switch (state_)
	{
	case S_READY:		UpdateReady();		break;
	case S_PLAY:			UpdatePlay();		break;
	case S_GAMEOVER:		UpdateGameOver();	break;
	}
}

//�X�V�F����
void PlayScene::UpdateReady()
{

	if (ReadyTimer_ > 0) {
		ReadyTimer_--;
		if (ReadyTimer_ == 0) {
			//�X�e�[�g�p�^�[����ύX����
			state_ = S_PLAY;
			//�^�C�}�[���J�n����
			Time_->TimeStart();
		}
	}
}

//�X�V�F�v���C��
void PlayScene::UpdatePlay()
{
	if (Time_->IsFinished()) {
		//�X�e�[�g�p�^�[����ύX����
		state_ = S_GAMEOVER;
	}
}

//�X�V�F�I��
void PlayScene::UpdateGameOver()
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
