/*======================================================

	[debugCamera.cpp]
	Author : 出合翔太

======================================================*/

#include "main.h"
#include "input.h"
#include "debugproc.h"
#include "DebugCamera.h"
#include "Camera.h"

//　マクロ定義
#define	CAM_POS_V_X		(0.0f)											// カメラの視点初期位置(X座標)
#define	CAM_POS_V_Y		(100.0f)										// カメラの視点初期位置(Y座標)
#define	CAM_POS_V_Z		(200.0f)										// カメラの視点初期位置(Z座標)
#define	CAM_POS_R_X		(0.0f)											// カメラの注視点初期位置(X座標)
#define	CAM_POS_R_Y		(0.0f)											// カメラの注視点初期位置(Y座標)
#define	CAM_POS_R_Z		(0.0f)											// カメラの注視点初期位置(Z座標)
#define	VIEW_ANGLE		(D3DXToRadian(70.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値	値より近いと描画しない
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値	値より遠いと描画しない
#define MOVE_CAMERA		(1.0f)
#define ROTATE_CAMERA	(D3DX_PI * 0.01f)
#define CAMERADISTANCE	(1.0f)

D3DXVECTOR3			DebugCamera::move;
D3DXVECTOR3			DebugCamera::rot;
float				DebugCamera::fDistance;

//#	カメラの初期化
void DebugCamera::Init()
{
	Camera::Init();
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						
	move = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	float x, z;
	x = posV.x - posR.x;
	z = posV.z - posR.z;
	fDistance = sqrtf(x * x + z * z);
}

//#	カメラの終了処理
void DebugCamera::Uninit()
{

}

//# カメラの更新処理
void DebugCamera::Update()
{
	if (Input::KB_IsPress(DIK_S))
	{
		posV.z += move.z;
		posR.z += move.z;
	}

	if (Input::KB_IsPress(DIK_W))
	{
		posR.z -= move.z;
		posV.z -= move.z;
	}

	if (Input::KB_IsPress(DIK_A))
	{
		posV.x += move.x;
		posR.x += move.x;
	}

	if (Input::KB_IsPress(DIK_D))
	{
		posV.x -= move.x;
		posR.x -= move.x;
	}
	if (Input::KB_IsPress(DIK_Z))
	{
		rot.y += ROTATE_CAMERA;
		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2.0f;
		}
		posR.x = posV.x - sinf(rot.y) * fDistance;
		posR.z = posV.z - cosf(rot.y) * fDistance;
	}

	if (Input::KB_IsPress(DIK_C))
	{
		rot.y -= ROTATE_CAMERA;
		if (rot.y < D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}
		posR.x = posV.x - sinf(rot.y) * fDistance;
		posR.z = posV.z - cosf(rot.y) * fDistance;
	}

	if (Input::KB_IsPress(DIK_Y))
	{
		posV.y += MOVE_CAMERA;
	}
	
	if (Input::KB_IsPress(DIK_N))
	{
		posV.y -= MOVE_CAMERA;
	}

	if (Input::KB_IsPress(DIK_E))
	{
		rot.y += ROTATE_CAMERA;
		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2.0f;
		}
		posR.x = posV.x - sinf(rot.y) * fDistance;
		posR.z = posV.z - cosf(rot.y) * fDistance;
	}
	
	if (Input::KB_IsPress(DIK_Q))
	{
		rot.y -= ROTATE_CAMERA;
		if (rot.y < D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}
		posR.x = posV.x + sinf(rot.y) * fDistance;
		posR.z = posV.z + cosf(rot.y) * fDistance;
	}

	if (Input::KB_IsPress(DIK_T))
	{
		posR.y += MOVE_CAMERA;
	}
	
	if (Input::KB_IsPress(DIK_B))
	{
		posR.y -= MOVE_CAMERA;
	}


	if (Input::KB_IsPress(DIK_U))
	{
		fDistance -= CAMERADISTANCE;
		if (fDistance < 100.0f)
		{
			fDistance = 100.0f;
		}
		posV.x = posR.x + sinf(rot.y) * fDistance;
		posV.z = posR.z + cosf(rot.y) * fDistance;
	}

	if (Input::KB_IsPress(DIK_M))
	{
		fDistance += CAMERADISTANCE;
		if (fDistance > 1000.0f)
		{
			fDistance = 1000.0f;
		}
		posV.x = posR.x + sinf(rot.y) * fDistance;
		posV.z = posR.z + cosf(rot.y) * fDistance;
	}

	if (Input::KB_IsPress(DIK_SPACE))
	{
		posV = D3DXVECTOR3(CAM_POS_V_X, CAM_POS_V_Y, CAM_POS_V_Z);	//	カメラ位置
		posR = D3DXVECTOR3(CAM_POS_R_X, CAM_POS_R_X, CAM_POS_R_X);	//	注視点
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//	カメラの上ベクトル

		float x, z;
		x = posV.x - posR.x;
		z = posV.z - posR.z;
		fDistance = sqrtf(x * x + z * z);
	}

	DebugProc_Print((char*)"カメラの視点 [%f : %f : %f]\n", posV.x, posV.y, posV.z);
	DebugProc_Print((char*)"カメラの注視点 [%f : %f : %f]\n", posR.x, posR.y, posR.z);
	DebugProc_Print((char*)"カメラの向き [%f]\n", rot.y);
	DebugProc_Print((char*)"カメラの距離[%f]\n", fDistance);
	DebugProc_Print((char*)"\n");
}

//#	カメラの設定
void DebugCamera::Set()
{
	Camera::Set();
}
