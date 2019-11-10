/*================================================

	[Scenedebug.cpp]
	Author : èoçá„ƒëæ

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

void SceneDebug::Init()
{
	DebugCamera::Init();
	Light::Init();
	Field::Init();
	DebugProc_Initialize();
}

void SceneDebug::Uninit()
{
	Field::Uninit();
	Light::Uninit();
	DebugCamera::Uninit();
	DebugProc_Finalize();
}

void SceneDebug::Update()
{
	DebugProc_Update();
	DebugCamera::Update();
}

void SceneDebug::Draw()
{
	DebugProc_Draw();
	Field::ActorDraw();
	Field::PlaneDraw();
	DebugCamera::Set();
}
