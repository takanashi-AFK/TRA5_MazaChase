#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

class StageMap : public GameObject
{
	CsvReader CsvMap_;
	int Width;//ก๐i[
	int Height;//c๐i[
	int** table_;
public:
	//RXgN^
	//๘Fparent  eIuWFNgiSceneManagerj
	StageMap(GameObject* parent);

	//๚ป
	void Initialize() override;

	//XV
	void Update() override;

	//`ๆ
	void Draw() override;

	//J๚
	void Release() override;
};