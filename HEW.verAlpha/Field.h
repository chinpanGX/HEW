/*===========================================================

	[Field.h]
	Author : 出合翔太

=============================================================*/

#pragma once
#include "Model.h"

//	マクロ定義
#define OBJECT_NUM 1	// Objectの数

//# Fieldクラス
/* ゲームの背景の描画をするクラス */
class Field
{
private:
	static Model *Object[OBJECT_NUM];					//	Model型ポインタ配列
public:
	static void Init();		//	初期化処理
	static void Uninit();	//	終了処理
	static void Draw();		//	描画処理
};

