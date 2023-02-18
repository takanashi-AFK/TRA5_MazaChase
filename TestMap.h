#pragma once
#include "Engine/GameObject.h"

enum
{
	TYPE_FLOOR,
	TYPE_WALL,
	TYPE_MAX,
};
//�e�X�g�V�[�����Ǘ�����N���X
class TestMap : public GameObject
{
private:

	int hModel_[TYPE_MAX];
	int Width;//�������i�[
	int Height;//�c�����i�[
	int** table_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TestMap(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�w�肵���ʒu���ʂ��̂��ʂ�Ȃ����𒲂ׂ�֐�
	//�����F_x,_y	 ���ׂ�ʒu
	//�ߒl�F�ʂ�� = true/�ʂ�Ȃ� = false
	bool IsWall(int _x, int _z);

};