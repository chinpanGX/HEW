
#include "light.h"
#include "main.h"

//!	ライトの種類　p110

#define	NUM_LIGHT		(3)		// ライトの数(9コまで)

// グローバル変数
D3DLIGHT9 g_aLight[NUM_LIGHT];		// ライト情報
LPDIRECT3DDEVICE9 Light::pDevice;

// ライトの初期化処理
void Light::Init()
{
	pDevice = GetD3DDevice();		//デバイスの取得
	
	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ライトのタイプの設定	(ディレクショナルライト)
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 環境光
	g_aLight[0].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.20f, -0.80f, 0.40f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(0, &g_aLight[0]);

	// ライトを有効に
	pDevice->LightEnable(0, TRUE);


	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	g_aLight[1].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

	// 環境光
	g_aLight[1].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

    // ライトの方向の設定
	vecDir = D3DXVECTOR3(-0.20f, 1.00f, -0.50f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &light->vecDir);

	// ライトをレンダリングパイプラインに設定
	light->pDevice->SetLight(1, &g_aLight[1]);

	// ライトを有効に
	light->pDevice->LightEnable(1, TRUE);	//ライトの数

	// ライティングモード有効…シェーディング処理
	light->pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

// ライトの終了処理
void Light::Uninit()
{
	
}

// ライトの更新処理
void Light::Update()
{
}


