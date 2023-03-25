
#include "PlayScene.h"

//��b�Ԃ̃t���[��������
const int FPS = 60;

//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"),Time_(0),ReadyTimer_(0),state_(0)
{
}

//������
void PlayScene::Initialize()
{

	Instantiate<Enemy>(this);
	Instantiate<StageMap>(this);
	Instantiate<Player>(this);

	//�^�C�}�[�̐ݒ�
	#if 0
	{
		
		Time_ = Instantiate<Timer>(this);
		Time_->DrawPostion(30, 30);	//�`�悷��ʒu���w��
		Time_->UseThis(T_TIMER);	//(State_)���g��
		Time_->SetLimit(30);//�������Ԃ�ݒ�(�b)
	}	
	#endif

	//�~�j�}�b�v�̐ݒ�
	#if 0
	{
		Map_ = Instantiate<MiniMap>(this);
		Map_->DrawPosition(3, 13);
		Map_->ChengeOpacity(190);
		ReadyTimer_ = (3 * FPS);//(�b * �t���[�����[�g)
	}
	#endif
}

//�X�V
void PlayScene::Update()
{
	switch (state_)
	{
	case S_READY:		UpdateReady();	break;
	case S_PLAY:		UpdatePlay();	break;
	case S_GAMEOVER:	UpdateClear();	break;
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
	//if (Time_->IsFinished()) {
	//	//�X�e�[�g�p�^�[����ύX����
	//	state_ = S_GAMEOVER;
	//}
}

//�X�V�F�I��
void PlayScene::UpdateClear()
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
