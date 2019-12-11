/*==================================

	[SceneGame.cpp]
	Author : 出合翔太

===================================*/

#include "SceneGame.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Character.h"
#include "main.h"
#include "light.h"
#include "debugproc.h"


//	ゲームの初期化処理
void SceneGame::Init()
{
	
	m_Character.Init(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Map.Init();
	Light::Init();
	m_Camera.Init();
	DebugProc_Initialize();
	
}

//	ゲームの終了処理
void SceneGame::Uninit()
{
	m_Character.Uninit();
	m_Map.Uninit();
	m_Camera.Uninit();
	DebugProc_Finalize();
}

//	ゲームの更新処理
void SceneGame::Update()
{

	m_Character.Update();
	m_Camera.Update();
	//if (KeyBoard::IsTrigger(DIK_W))
	{
		//SceneManager::ChangeSceneState();
	}

}

//	ゲームの描画処理
void SceneGame::Draw()
{
	//	ワイヤーフレームをセット
	//pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_Character.Draw();
	m_Map.Draw();
	m_Camera.Set();
	DebugProc_Draw();
}
