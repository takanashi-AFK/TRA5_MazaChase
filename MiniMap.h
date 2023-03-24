#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"

#include "StageObject.h"
#include "StageMap.h"
#include "Player.h"

#include <vector>
using std::vector;


enum {
	MAP_FLOOR,
	MAP_WALL,
	MAP_PLAYER,
	MAP_MAX,
};
class MiniMap:public GameObject
{
private:
	int Width_, Height_;
	float DrawX_, DrawY_;//�`�悳�����W
	int Opacity_;
	float MapSize_;
	Transform MapTrans_;
	Transform PlayerTrans_;

public:
	int hPict_[MAP_MAX];	//���f���ԍ�

	vector<vector<int>> pTable_;
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MiniMap(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�`��ʒu��ݒ肷��֐�
	void DrawPosition(float _x, float _y) { this->DrawX_ = _x * 0.01; this->DrawY_ = _y * -0.01; }

	//�`��T�C�Y��ݒ肷��֐�
	//void DrawSize(float _size);

	//�s�����x��ύX����֐�
	void ChengeOpacity(int _Opa) { this->Opacity_ = _Opa; }
};

