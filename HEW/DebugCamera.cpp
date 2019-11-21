/*======================================================

	[debugCamera.cpp]
	Author : 出合翔太

======================================================*/

#include "DebugCamera.h"

#include "main.h"
#include "input.h"
#include "debugproc.h"


//　マクロ定義
#define	CAM_POS_V_X		(0.0f)											// カメラの視点初期位置(X座標)
#define	CAM_POS_V_Y		(100.0f)										// カメラの視点初期位置(Y座標)
#define	CAM_POS_V_Z		(-200.0f)										// カメラの視点初期位置(Z座標)
#define	CAM_POS_R_X		(0.0f)											// カメラの注視点初期位置(X座標)
#define	CAM_POS_R_Y		(0.0f)											// カメラの注視点初期位置(Y座標)
#define	CAM_POS_R_Z		(0.0f)											// カメラの注視点初期位置(Z座標)
#define	VIEW_ANGLE		(D3DXToRadian(70.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値	値より近いと描画しない
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値	値より遠いと描画しない


D3DXVECTOR3 DebugCamera::m_Velocity;

//#	カメラの初期化
void DebugCamera::Init()
{
	Camera::Init();
	m_Velocity = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
}

//#	カメラの終了処理
void DebugCamera::Uninit()
{

}

//# カメラの更新処理
void DebugCamera::Update()
{
	if(Input::KB_IsPress(DIK_W))
	{
		posV.z += m_Velocity.z;
		posR.z += m_Velocity.z;
	}

	if (Input::KB_IsPress(DIK_S))
	{
		posR.z -= m_Velocity.z;
		posV.z -= m_Velocity.z;
	}

	if (Input::KB_IsPress(DIK_D))
	{
		posV.x += m_Velocity.x;
		posR.x += m_Velocity.x;
	}

	if (Input::KB_IsPress(DIK_A))
	{
		posV.x -= m_Velocity.x;
		posR.x -= m_Velocity.x;
	}
	
	if (Input::KB_IsPress(DIK_SPACE))
	{
		posV.y += m_Velocity.y;
		posR.y += m_Velocity.y;
	}

	if (Input::KB_IsPress(DIK_LSHIFT))
	{
		posV.y -= m_Velocity.y;
		posR.y -= m_Velocity.y;
	}
	
	if (Input::KB_IsPress(DIK_E))
	{
		posR.x += m_Velocity.x;
	}
	
	if (Input::KB_IsPress(DIK_Q))
	{
		posR.x -= m_Velocity.x;
	}

	if (Input::KB_IsPress(DIK_R))
	{
		posR.y += m_Velocity.y;
	}

	if (Input::KB_IsPress(DIK_F))
	{
		posR.y -= m_Velocity.y;
	}

	if (Input::KB_IsTrigger(DIK_Z))
	{
		Init();
	}
	DebugProc_Print((char*)"*** ３Ｄポリゴン操作 ***\n");
	DebugProc_Print((char*)"位置 [%f : %f : %f]\n", posV.x, posV.y, posV.z);
	DebugProc_Print((char*)"前移動 : Ｗ\n");
	DebugProc_Print((char*)"後移動 : Ｓ\n");
	DebugProc_Print((char*)"左移動 : Ａ\n");
	DebugProc_Print((char*)"右移動 : Ｄ\n");
	DebugProc_Print((char*)"上移動 : SPACE\n");
	DebugProc_Print((char*)"下移動 : LSHIFT\n");
	DebugProc_Print((char*)"\n");

	DebugProc_Print((char*)"向き [%f : %f : %f]\n", posR.x, posR.y, posR.z);
	DebugProc_Print((char*)"X軸回転 : Q / E\n");
	DebugProc_Print((char*)"Y軸回転 : R / F\n");
	DebugProc_Print((char*)"\n");

	DebugProc_Print((char*)"位置・向きリセット : Z\n");
}

//#	カメラの設定
void DebugCamera::Set()
{
	Camera::Set();
}
