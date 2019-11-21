/*==============================================

	[camera.cpp]										
	Author : 出合翔太									

===============================================*/
#include "main.h"
#include "Camera.h"

//#	グローバル変数
D3DXVECTOR3			Camera::posV;			// 視点（カメラの位置）
D3DXVECTOR3			Camera::posR;			// 注視点（カメラはどこを見ているのか）
D3DXVECTOR3			Camera::vecU;			// 上方向ベクトル（カメラの上方向はｙがプラス）座標は（０，１，０）
D3DXMATRIX			Camera::mtxProjection;	// プロジェクションマトリックス
D3DXMATRIX			Camera::mtxView;		// ビューマトリックス
LPDIRECT3DDEVICE9	Camera::pDevice;		//　デバイスの取得用変数

//#	カメラの初期化
void Camera::Init()
{
	posV = D3DXVECTOR3(CAM_POS_V_X, CAM_POS_V_Y, CAM_POS_V_Z);	//カメラ位置
	posR = D3DXVECTOR3(CAM_POS_R_X, CAM_POS_R_X, CAM_POS_R_X);	//注視点
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);							//カメラの上ベクトル
}

//#	カメラの終了処理
void Camera::Uninit()
{
	
}

//#	カメラの設定
void Camera::Set()
{
	//デバイスの取得
	pDevice = GetD3DDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		VIEW_ANGLE,				// ビュー平面の視野角
		VIEW_ASPECT,			// ビュー平面のアスペクト比
		VIEW_NEAR_Z,			// ビュー平面のNearZ値
		VIEW_FAR_Z);			// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);	//	単位行列:行列の初期化するときに使う

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView,
		&posV,		// カメラの視点
		&posR,		// カメラの注視点
		&vecU);	// カメラの上方向ベクトル

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
