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
#include "mondai.h"

SceneDebug::SceneDebug()
{
	m_pDebugCamera = new DebugCamera;
}

SceneDebug::~SceneDebug()
{
	delete m_pDebugCamera;
}

//# デバッグシーンの初期化 
void SceneDebug::Init()
{
	m_pDebugCamera->Init();
	Light::Init();
	Map::Init();
	DebugProc_Initialize();
	//Mondai::Init();
}

//# デバッグシーンの終了処理
void SceneDebug::Uninit()
{
	m_pDebugCamera->Uninit();
	Map::Uninit();
	Light::Uninit();
	DebugProc_Finalize();
	//Mondai::Uninit();
}

//# デバッグシーンの更新処理
void SceneDebug::Update()
{
	m_pDebugCamera->Update();
	//Mondai::Update();
}

//# デバッグシーンの描画処理
void SceneDebug::Draw()
{
	m_pDebugCamera->Set();
	DebugProc_Draw();
	Map::Draw();

	//Mondai::Draw();
}
