/*================================================

	[Scenedebug.cpp]
	Author : 出合翔太

=================================================*/

#include "SceneDebug.h"
#include "light.h"

//# デバッグシーンの初期化 
void SceneDebug::Init()
{
	//LPDIRECT3DDEVICE9 pD3DDevice = GetD3DDevice();
	//m_Map.Init();
	Light::Init();
	m_Camera.Init();
	//m_Character.Init();
	//DebugProc_Initialize();
	//m_Sprite.Init(pD3DDevice);
	m_mondai.Init();
	
}

//# デバッグシーンの終了処理
void SceneDebug::Uninit()
{
	m_mondai.Uninit();
	//m_Map.Uninit();
	Light::Uninit();
	m_Camera.Uninit();
	//m_Character.Uninit();
	//DebugProc_Finalize();
	//m_Sprite.Uninit();
}

//# デバッグシーンの更新処理
void SceneDebug::Update()
{
	m_mondai.Update();
	m_Camera.Update();
	//m_Character.Update();
}

//# デバッグシーンの描画処理
void SceneDebug::Draw()
{
	m_mondai.Draw();
	//DebugProc_Draw();
	//m_Map.Draw();
	m_Camera.Set();
	//m_Character.Draw();
	//m_Sprite.Draw(TEXTURE_INDEX_QUIZSAMPLE,0.0f,0.0f,0.0f);
}
