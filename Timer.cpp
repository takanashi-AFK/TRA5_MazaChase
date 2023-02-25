#include "Timer.h"

static const int FPS = 60;

// �R���X�g���N�^
Timer::Timer(GameObject * parent)
	: GameObject(parent, "Timer"), State_(0),Frame_(0),Active_(false),DrawX_(0), DrawY_(0)
{
	//�e�L�X�g�̃��[�h
	pText = new Text;
	pText->Initialize();
}

//�f�X�g���N�^
Timer::~Timer()
{
	delete pText;
}

//������
void Timer::Initialize()
{
	Frame_ = 0;
	State_ = 0;
	Active_ = false;
}

//�X�V
void Timer::Update()
{
	switch (State_)
	{
	case T_TIMER:		TimerUpdate();		break;
	case T_STOPWATCH: StopWatchUpdate();	break;
	}
}

//�X�V�FTimer
void Timer::TimerUpdate()
{
	if (Active_)//�A�N�e�B�u���̂݃J�E���g�𓮂���
		if (Frame_ > 0)
		{
			Frame_--;
		}
}

//�X�V�FStopWatch
void Timer::StopWatchUpdate()
{
	if (Active_)//�A�N�e�B�u���̂݃J�E���g�𓮂���
		Frame_++;
}

//�`��
void Timer::Draw()
{
	pText->Draw(DrawX_, DrawY_, "Time:");
	int Sec = Frame_ / FPS;
	pText->Draw(DrawX_+90, DrawY_, Sec);
}

//�J��
void Timer::Release()
{
}

//�g�p����@�\��ύX����֐�
//�����F_state�@(Timer::TIMER) / (Timer::STOPWATCH)
void Timer::UseThis(int _state)
{
	State_ = _state;
}

//�������Ԃ����߂�֐�
void Timer::SetLimit(float seconds_)
{
	Frame_ = (int)(seconds_ * FPS);
}

//�J�E���g���J�n����֐�
void Timer::TimeStart()
{
	Active_ = true;
}

//�J�E���g���I������֐�
void Timer::TimeStop()
{
	Active_ = false;
}

//�I����������m�点��֐�
bool Timer::IsFinished()
{
	return(Frame_ == 0);
}

//���f��������m�点��֐�
bool Timer::IsStopped()
{
	return(Active_ == false);
}