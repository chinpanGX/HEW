/*=================================================

	[TitleCamera.h]
	Author : 出合翔太

=================================================*/

#pragma once
#include "Camera.h"

//# TitleCameraクラス : 基底クラスCameraの派生 
/*  */
class TitleCamera :public Camera
{
public:
	TitleCamera();
	~TitleCamera();
	void Init();
	void Uninit();
	void Update();
	void Set();
};

