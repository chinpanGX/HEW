/*======================================================

	[debugCamera.cpp]
	Author : 出合翔太

======================================================*/

#include "DebugCamera.h"

#include "main.h"
#include "Camera.h"
#include "input.h"
#include "debugproc.h"

//#	グローバル変数
DebugCamera *g_camera = new DebugCamera;	//インスタンスの生成

//#	カメラの初期化
void DebugCamera::Init()
{
	g_camera->posV = D3DXVECTOR3(CAM_POS_V_X, CAM_POS_V_Y, CAM_POS_V_Z);	//カメラ位置
	g_camera->posR = D3DXVECTOR3(CAM_POS_R_X, CAM_POS_R_X, CAM_POS_R_X);	//注視点
	g_camera->vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);							//カメラの上ベクトル
	g_camera->move = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
}

//#	カメラの終了処理
void DebugCamera::Uninit()
{
	delete g_camera;
}

void DebugCamera::Update()
{
	if(Input::KB_IsPress(DIK_W))
	{
		g_camera->posV.z += g_camera->move.z;
		g_camera->posR.z += g_camera->move.z;
	}

	if (Input::KB_IsPress(DIK_S))
	{
		g_camera->posR.z -= g_camera->move.z;
		g_camera->posV.z -= g_camera->move.z;
	}

	if (Input::KB_IsPress(DIK_D))
	{
		g_camera->posV.x += g_camera->move.x;
		g_camera->posR.x += g_camera->move.x;
	}

	if (Input::KB_IsPress(DIK_A))
	{
		g_camera->posV.x -= g_camera->move.x;
		g_camera->posR.x -= g_camera->move.x;
	}
	
	if (Input::KB_IsPress(DIK_SPACE))
	{
		g_camera->posV.y += g_camera->move.y;
		g_camera->posR.y += g_camera->move.y;
	}

	if (Input::KB_IsPress(DIK_LSHIFT))
	{
		g_camera->posV.y -= g_camera->move.y;
		g_camera->posR.y -= g_camera->move.y;
	}
	
	if (Input::KB_IsPress(DIK_E))
	{
		g_camera->posR.x += g_camera->move.x;
	}
	
	if (Input::KB_IsPress(DIK_Q))
	{
		g_camera->posR.x -= g_camera->move.x;
	}

	if (Input::KB_IsPress(DIK_R))
	{
		g_camera->posR.y += g_camera->move.y;
	}

	if (Input::KB_IsPress(DIK_F))
	{
		g_camera->posR.y -= g_camera->move.y;
	}

	if (Input::KB_IsTrigger(DIK_Z))
	{
		g_camera->Init();
	}
	DebugProc_Print((char*)"*** ３Ｄポリゴン操作 ***\n");
	DebugProc_Print((char*)"位置 [%f : %f : %f]\n", g_camera->posV.x, g_camera->posV.y, g_camera->posV.z);
	DebugProc_Print((char*)"前移動 : Ｗ\n");
	DebugProc_Print((char*)"後移動 : Ｓ\n");
	DebugProc_Print((char*)"左移動 : Ａ\n");
	DebugProc_Print((char*)"右移動 : Ｄ\n");
	DebugProc_Print((char*)"上移動 : SPACE\n");
	DebugProc_Print((char*)"下移動 : LSHIFT\n");
	DebugProc_Print((char*)"\n");

	DebugProc_Print((char*)"向き [%f : %f : %f]\n", g_camera->posR.x, g_camera->posR.y, g_camera->posR.z);
	DebugProc_Print((char*)"X軸回転 : Q / E\n");
	DebugProc_Print((char*)"Y軸回転 : R / F\n");
	DebugProc_Print((char*)"\n");

	DebugProc_Print((char*)"位置・向きリセット : Z\n");
}

//#	カメラの設定
void DebugCamera::Set()
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
