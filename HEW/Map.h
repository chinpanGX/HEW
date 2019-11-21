/*========================================================

	[Map.h]
	Author : 出合翔太

=========================================================*/

#pragma once
#include "Model.h"

//	マクロ定義
#define ACTOR_NUM 1	// 3Dモデルの数

//# Mapクラス
/* マップを管理するクラス */
class Map
{
private:
	static Model *Actor[ACTOR_NUM];		//	Model型ポインタ配列
public:
	void Init();
	void Uninit();
	void Draw();
};

