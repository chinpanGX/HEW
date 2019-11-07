
#include "light.h"
#include "main.h"

//!	ライトの種類　p110

#define	NUM_LIGHT		(3)		// ライトの数(9コまで)

// グローバル変数
Light *light = new Light;
D3DLIGHT9 g_aLight[NUM_LIGHT];		// ライト情報

// ライトの初期化処理
void Light::Init()
{
	light->pDevice = GetD3DDevice();		//デバイスの取得
	
	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ライトのタイプの設定	(ディレクショナルライト)
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 環境光
	g_aLight[0].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	// ライトの方向の設定
	light->vecDir = D3DXVECTOR3(0.20f, -0.80f, 0.40f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &light->vecDir);

	// ライトをレンダリングパイプラインに設定
	light->pDevice->SetLight(0, &g_aLight[0]);

	// ライトを有効に
	light->pDevice->LightEnable(0, TRUE);


	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	g_aLight[1].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

	// 環境光
	g_aLight[1].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

    // ライトの方向の設定
	light->vecDir = D3DXVECTOR3(-0.20f, 1.00f, -0.50f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &light->vecDir);

	// ライトをレンダリングパイプラインに設定
	light->pDevice->SetLight(1, &g_aLight[1]);

	// ライトを有効に
	light->pDevice->LightEnable(1, TRUE);	//ライトの数

#if 0
	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[2], sizeof(D3DLIGHT9));

	// ライト2のタイプの設定
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	// ライト2の拡散光の設定
	g_aLight[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	// ライト2の鏡面反射光の設定
	g_aLight[2].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

    // ライト2の方向の設定
	light->vecDir = D3DXVECTOR3(0.80f, 0.10f, 0.40f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[2].Direction, &light->vecDir);

	// ライト2をレンダリングパイプラインに設定
	light->pDevice->SetLight(2, &g_aLight[2]);

	// ライト2を有効に
	light->pDevice->LightEnable(2, TRUE);

#endif
	// ライティングモード有効…シェーディング処理
	light->pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void Light::Uninit()
{
	delete light;
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void Light_Update(void)
{
}

