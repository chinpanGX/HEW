/*===============================================

	[Camera.h]
	Author : 出合翔太

=================================================*/

#pragma once
#include "main.h"

//　マクロ定義
#define	CAM_POS_V_X		(0.0f)											// カメラの視点初期位置(X座標)
#define	CAM_POS_V_Y		(100.0f)										// カメラの視点初期位置(Y座標)
#define	CAM_POS_V_Z		(-200.0f)										// カメラの視点初期位置(Z座標)
#define	CAM_POS_R_X		(0.0f)											// カメラの注視点初期位置(X座標)
#define	CAM_POS_R_Y		(0.0f)											// カメラの注視点初期位置(Y座標)
#define	CAM_POS_R_Z		(0.0f)											// カメラの注視点初期位置(Z座標)
#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値	値より近いと描画しない
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値	値より遠いと描画しない

//　
class Camera
{
private:
	//メンバ変数
	D3DXVECTOR3			posV;			// 視点（カメラの位置）
	D3DXVECTOR3			posR;			// 注視点（カメラはどこを見ているのか）
	D3DXVECTOR3			vecU;			// 上方向ベクトル（カメラの上方向はｙがプラス）座標は（０，１，０）
	D3DXMATRIX			mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX			mtxView;		// ビューマトリックス
	LPDIRECT3DDEVICE9	pDevice;		//　デバイスの取得用変数

public:
	//　メンバ関数
	static void Init();			//カメラの初期化
	static void Uninit();		//カメラの終了処理
	static void Set();			//カメラの設定
};



