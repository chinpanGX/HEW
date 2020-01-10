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
#include "BillBoard.h"
#include "camera.h"

//	ゲームの初期化処理
void SceneGame::Init()
{
	
	DebugProc_Initialize();
	m_Character.Init(D3DXVECTOR3(0.0f, 50.0f, 48.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Map.Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(100.0f,100.0f,100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Light::Init();
	//m_Camera.Init();
	Camera_Initialize();
	//BillBoard_Init();
}

//	ゲームの終了処理
void SceneGame::Uninit()
{
	Camera_Finalize();
	m_Character.Uninit();
	//m_Map.Uninit();
	//m_Camera.Uninit();
	//DebugProc_Finalize();
	
	//BillBoard_Uninit();
}

//	ゲームの更新処理
void SceneGame::Update()
{
	Camera_Update();
	m_Character.Update();
	m_Camera.Update();
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
	//Camera.Set();
	DebugProc_Draw();
	
}

Character * SceneGame::SetCharacter()
{
	return &m_Character;
}

Field * SceneGame::SetField()
{
	return &m_Map;
}
