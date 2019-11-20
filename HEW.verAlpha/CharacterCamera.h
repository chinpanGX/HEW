/*====================================================

	[CharacterCamera.h]
	Author : 出合翔太

=====================================================*/

#pragma once
#include "CameraBase.h"

//#	CharacterCameraクラス
/* キャラクターにつけるカメラ */
class CharacterCamera :public CameraBase
{
public:
	void Init();
	void Uninit();
	void Set();
};

