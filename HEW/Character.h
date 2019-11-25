/*============================================

[Character.h]
Author : hohman yuushi

=============================================*/

#pragma once
#include "main.h"
#include "CharacterCamera.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float getRadian(float X1, float Y1, float X2, float Y2);

//#	キャラクタークラス
/* キャラクターの情報を管理するクラス　*/
class Character
{
private:
	CharacterCamera m_Camera;	//	キャラクターにつけるカメラのインスタンス
public:
	Character();
	~Character();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};



