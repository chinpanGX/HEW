/*==================================

	[SceneGame.cpp]
	概要 : ゲームシーンを管理する
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
<<<<<<< HEAD
	Camera_Initialize();
	m_Character.Init(D3DXVECTOR3(0.0f, 50.0f, 220.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
=======
	m_Camera.Init();
	m_Character.Init(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
>>>>>>> refactoring
	m_Map.Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(100.0f,100.0f,100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

//	ゲームの終了処理
void SceneGame::Uninit()
{
	m_Camera.Uninit();
	m_Character.Uninit();
	m_Map.Uninit();
	DebugProc_Finalize();
}

//	ゲームの更新処理
void SceneGame::Update()
{
	m_Camera.Update();
	//m_Character.Update();
	if (KeyBoard::IsTrigger(DIK_T))
	{
		SceneManager::ChangeSceneState();
	}
}

//	ゲームの描画処理
void SceneGame::Draw()
{
	m_Camera.Set();
	m_Character.Draw();
	//m_Map.Draw();
	m_Score.Draw(SCREEN_WIDTH - 100.0f,0.0f,m_Character.GetScore(),5,0);
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

Camera * SceneGame::SetCamera()
{
	return &m_Camera;
}
