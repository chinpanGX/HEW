/*================================================

	[Scenedebug.cpp]
	Author : 出合翔太

=================================================*/

#include "SceneDebug.h"
#include "SceneManager.h"
#include "input.h"
#include "XFile.h"
#include "Model.h"
#include "main.h"
#include "DebugCamera.h"
#include "light.h"
#include "Field.h"
#include "debugproc.h"

//# デバッグシーンの初期化 
void SceneDebug::Init()
{
	DebugCamera::Init();
	Light::Init();
	Field::Init();
	DebugProc_Initialize();
}

//# デバッグシーンの終了処理
void SceneDebug::Uninit()
{
	Field::Uninit();
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
	Field::ActorDraw();
	Field::PlaneDraw();
	DebugCamera::Set();
}
