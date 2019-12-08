/*================================================

	[Scenedebug.cpp]
	Author : 出合翔太

=================================================*/

#include "SceneDebug.h"
#include "SceneManager.h"
#include "main.h"
#include "DebugCamera.h"
#include "light.h"
#include "debugproc.h"
//#include "Map.h"

//# デバッグシーンの初期化 
void SceneDebug::Init()
{
	//LPDIRECT3DDEVICE9 pD3DDevice = GetD3DDevice();
	m_Map.Init();
	Light::Init();
	//m_Camera.Init();
	//m_Character = new Model(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_pXFileList["asset/model/dai.x"]);
	m_Character.Init(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	//DebugProc_Initialize();
	//m_Sprite.Init(pD3DDevice);
}

//# デバッグシーンの終了処理
void SceneDebug::Uninit()
{
	m_Map.Uninit();
	//m_Camera.Uninit();
	m_Character.Uninit();
	//DebugProc_Finalize();
	//m_Sprite.Uninit();
}

//# デバッグシーンの更新処理
void SceneDebug::Update()
{
	//m_Camera.Update();

	//m_Character.Update();
	m_Count.Update();
	m_Character.Update();

}

//# デバッグシーンの描画処理
void SceneDebug::Draw()
{
	//DebugProc_Draw();
	m_Map.Draw();
	//m_Camera.Set();

	m_Character.Draw();
	//m_Sprite.Draw(TEXTURE_INDEX_QUIZSAMPLE,1024,256,0,0,0,0,1,1,1);
	m_Count.Draw();

}
