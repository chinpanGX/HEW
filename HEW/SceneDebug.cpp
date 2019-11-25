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
#include "Map.h"

//# デバッグシーンの初期化 
void SceneDebug::Init()
{
	m_Map.Init();
	Light::Init();
	//m_Camera.Init();
	m_Character.Init();
	DebugProc_Initialize();
}

//# デバッグシーンの終了処理
void SceneDebug::Uninit()
{
	m_Map.Uninit();
	Light::Uninit();
	//m_Camera.Uninit();
	m_Character.Uninit();
	DebugProc_Finalize();
}

//# デバッグシーンの更新処理
void SceneDebug::Update()
{
	//m_Camera.Update();
	m_Character.Update();
}

//# デバッグシーンの描画処理
void SceneDebug::Draw()
{
	DebugProc_Draw();
	m_Map.Draw();
	//m_Camera.Set();
	m_Character.Draw();
}
