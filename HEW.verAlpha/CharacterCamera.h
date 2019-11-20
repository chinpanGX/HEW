/*====================================================

	[CharacterCamera.h]
	Author : 出合翔太

=====================================================*/

#pragma once
#include "main.h"
#include "Camera.h"

//#	CharacterCameraクラス : 基底クラスCameraの派生
/* キャラクターにつけるカメラ */
class CharacterCamera :public Camera
{
public:
	void Init();
	void Uninit();
	void Update();
	void Set();
};

