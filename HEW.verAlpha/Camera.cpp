/*=====================================

	[Camera.cpp]
	Author : 出合翔太

=======================================*/

#include "main.h"
#include "Camera.h"

Camera *g_camera = new Camera;	//インスタンスの生成

Camera::Camera()
{
	g_camera->posV = D3DXVECTOR3(CAM_POS_V_X, CAM_POS_V_Y, CAM_POS_V_Z);	//カメラ位置
	g_camera->posR = D3DXVECTOR3(CAM_POS_R_X, CAM_POS_R_X, CAM_POS_R_X);	//注視点
	g_camera->vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//カメラの上ベクトル
}


Camera::~Camera()
{
	delete g_camera;
	DEVICE_RELEASE(pDevice);
}

void Camera::Init()
{
}

void Camera::Uninit()
{
}

void Camera::Set()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera->mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera->mtxProjection,
		VIEW_ANGLE,				// ビュー平面の視野角
		VIEW_ASPECT,			// ビュー平面のアスペクト比
		VIEW_NEAR_Z,			// ビュー平面のNearZ値
		VIEW_FAR_Z);			// ビュー平面のFarZ値

// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera->mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera->mtxView);	//	単位行列:行列の初期化するときに使う

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera->mtxView,
		&g_camera->posV,		// カメラの視点
		&g_camera->posR,		// カメラの注視点
		&g_camera->vecU);	// カメラの上方向ベクトル

// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera->mtxView);
}
