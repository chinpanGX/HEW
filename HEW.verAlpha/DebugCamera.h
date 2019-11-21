/*==============================================
	
	[DebugCamera.h]
	Author : 出合翔太

==============================================*/

#pragma once
#include "main.h"
#include "CameraBase.h"
#include "Camera.h"

//# DebugCameraクラス　：　基底クラスCameraの派生
/* デバッグ用カメラ */
class DebugCamera : public Camera
{
private:
	//	メンバー変数
	static D3DXVECTOR3			move;			//	移動
	static D3DXVECTOR3			rot;			//	回転
	static float				fDistance;		//	視点と注視点の距離
public:
	//	メンバー関数
	void Init();		//	カメラの初期化
	void Uninit();		//	カメラの終了処理
	void Update();		//	カメラの更新
	void Set();			//	カメラの設定
};

