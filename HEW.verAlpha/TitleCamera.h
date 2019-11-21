/*=================================================

	[TitleCamera.h]
	Author : 出合翔太

=================================================*/

#pragma once
#include "main.h"
#include "Camera.h"

//# TitleCameraクラス : 基底クラスCameraの派生 
/* タイトルでマップを描画するためのカメラ */
class TitleCamera :public Camera
{
private:
	static D3DXVECTOR3 m_Velocity;	//	カメラの移動速度
public:
	void Init();	//	カメラの初期化
	void Uninit();	//	カメラの終了処理
	void Update();	//	カメラの更新処理
	void Set();		//	カメラの設定
};

