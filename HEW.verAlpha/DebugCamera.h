/*==============================================
	
	[DebugCamera.h]
	Author : 出合翔太

==============================================*/

#pragma once
#include "main.h"
#include "Camera.h"

//# DebugCamera
/* デバッグ用カメラ */
class DebugCamera : public Camera
{
private:
	
	//メンバ変数
	static D3DXVECTOR3			m_Velocity;		//	移動

public:
	//　メンバ関数
	void Init();		//	カメラの初期化
	void Uninit();		//	カメラの終了処理
	void Update();		//	カメラの更新
	void Set();			//	カメラの設定
};

