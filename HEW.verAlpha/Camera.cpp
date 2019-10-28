/*==============================================

	[camera.cpp]										//#	DirectXは左手座標系
	Author : 出合翔太									//#	OpenGLは右手座標系

===============================================*/
#include "main.h"
#include "Camera.h"

//#	グローバル変数
Camera *g_camera = new Camera;	//インスタンスの生成

//#	カメラの初期化
void Camera::Init()
{
	g_camera->posV = D3DXVECTOR3(CAM_POS_V_X, CAM_POS_V_Y, CAM_POS_V_Z);	//カメラ位置
	g_camera->posR = D3DXVECTOR3(CAM_POS_R_X, CAM_POS_R_X, CAM_POS_R_X);	//注視点
	g_camera->vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//カメラの上ベクトル
}

//#	カメラの終了処理
void Camera::Uninit()
{
	delete g_camera;
}

//#	カメラの設定
void Camera::Set()
{
	//デバイスの取得
	g_camera->pDevice = GetD3DDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera->mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera->mtxProjection,
		VIEW_ANGLE,				// ビュー平面の視野角
		VIEW_ASPECT,			// ビュー平面のアスペクト比
		VIEW_NEAR_Z,			// ビュー平面のNearZ値
		VIEW_FAR_Z);			// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	g_camera->pDevice->SetTransform(D3DTS_PROJECTION, &g_camera->mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera->mtxView);	//	単位行列:行列の初期化するときに使う

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera->mtxView,
		&g_camera->posV,		// カメラの視点
		&g_camera->posR,		// カメラの注視点
		&g_camera->vecU);	// カメラの上方向ベクトル

	// ビューマトリックスの設定
	g_camera->pDevice->SetTransform(D3DTS_VIEW, &g_camera->mtxView);
}
