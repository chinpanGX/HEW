/*============================================

[Character.h]
Author : hohman yuushi

=============================================*/

#pragma once
#include "main.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float getRadian(float X1, float Y1, float X2, float Y2);

	//#	キャラクタークラス :　親クラス

	/* キャラクターの情報を管理するクラス　*/
	class Character
{
public:
	Character();
	~Character();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};



