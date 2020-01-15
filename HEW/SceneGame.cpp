/*==================================

	[SceneGame.cpp]
	Author : 出合翔太

===================================*/

#include "SceneGame.h"
#include "SceneManager.h"
#include "Controller.h"
#include "main.h"
#include "light.h"
#include "debugproc.h"
#include "camera.h"

//	ゲームの初期化処理
void SceneGame::Init()
{
	DebugProc_Initialize();
	Light::Init();
	Camera_Initialize();
	m_Character.Init(D3DXVECTOR3(0.0f, 50.0f, 48.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Map.Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(100.0f,100.0f,100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//	ゲームの終了処理
void SceneGame::Uninit()
{
	Camera_Finalize();
	m_Character.Uninit();
	m_Map.Uninit();
	DebugProc_Finalize();
}

//	ゲームの更新処理
void SceneGame::Update()
{
	Camera_Update();
	m_Character.Update();
	Camera_Update();
	if (KeyBoard::IsTrigger(DIK_T))
	{
		SceneManager::ChangeSceneState();
	}
}

//	ゲームの描画処理
void SceneGame::Draw()
{
	//	ワイヤーフレームをセット
	//pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	Camera_SetCamera();
	m_Character.Draw();
	m_Map.Draw();
	DebugProc_Draw();
}

bool SceneGame::EndCheck()
{
	return false;
}


Character * SceneGame::SetCharacter()
{
	return &m_Character;
}

Field * SceneGame::SetField()
{
	return &m_Map;
}
