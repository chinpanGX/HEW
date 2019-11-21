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
	DebugCamera::Init();
	Light::Init();
	Map::Init();
	DebugProc_Initialize();
}

//# デバッグシーンの終了処理
void SceneDebug::Uninit()
{
	Map::Uninit();
	Light::Uninit();
	DebugCamera::Uninit();
	DebugProc_Finalize();
}

//# デバッグシーンの更新処理
void SceneDebug::Update()
{
	DebugCamera::Update();
}

//# デバッグシーンの描画処理
void SceneDebug::Draw()
{
	DebugProc_Draw();
	Map::Draw();
	DebugCamera::Set();
}
