/*========================================================

	[Map.h]
	Author : 出合翔太

=========================================================*/

#pragma once
#include "Field.h"
#include "Model.h"

//	マクロ定義
#define ACTOR_NUM 1	// 3Dモデルの数

//# Mapクラス
/* マップを管理するクラス */
class Map
{
private:
	static Model *Actor[ACTOR_NUM];		//	Model型ポインタ配列
	static Field *pField[1];				//	Field型ポインタ
public:
	static void Init();
	static void Uninit();
	static void Draw();
};

