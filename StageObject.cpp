#include "StageObject.h"

//コンストラクタ
StageObject::StageObject(GameObject* parent)
	: GameObject(parent, "StageObject"),obj_(0)
{
}

//初期化
void StageObject::Initialize()
{
	//ファイルネームを入れる配列
	const char* fileName[] = { "Floor.fbx","Wall.fbx" };

	for (int i = 0; i < OBJ_MAX; i++)
	{
		//モデルデータのロード
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}
	transform_.scale_ = { 2,2,2 };
}

//更新
void StageObject::Update()
{
}

//描画
void StageObject::Draw()
{
	Model::SetTransform(hModel_[obj_], transform_);
	Model::Draw(hModel_[obj_]);
}

//開放
void StageObject::Release()
{
}

//配置するobjectを変更する関数
void StageObject::ObjectSet(int _obj)
{
	obj_ = _obj;
}

//任意のゲームオブジェクトに「何メートル先でぶつかるか」を求める関数
int StageObject::GetModelHandle(int _obj)
{
	return (hModel_[_obj]);
}
