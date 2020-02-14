/*==============================================

	[SceneManager.cpp]	
	概要 : ゲームループを管理する
	Author : 出合翔太

===============================================*/
#include "main.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneTutorial.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "Sound.h"

//	スタティック変数
SceneBase			*SceneManager::m_scene[4];	//	シーンのインスタンスを格納[シーンの配列]
SCENE_STATE			SceneManager::m_sceneState;				//	シーンのステートマシン（シーンの状態を格納）
LPDIRECT3DDEVICE9	SceneManager::p3DDevice;				//	デバイス

//	初期化処理
void SceneManager::Init()
{
	p3DDevice = GetD3DDevice();			//	デバイスの取得

	//	メモリの確保
	m_scene[0] = new SceneTitle;		
	m_scene[1] = new SceneTutorial;		
	m_scene[2] = new SceneGame;			
	m_scene[3] = new SceneResult;

	Sound::Play(S_BGM_TITLE);
	m_sceneState = SCENE_TITLE;			//	初期シーンの設定(ゲームを起動したときの最初のシーン)
	m_scene[m_sceneState]->Init();		//	初期シーンの初期化
}

//	終了処理
void SceneManager::Uninit()
{
	//	各シーンのUninit関数を呼び出す
	m_scene[3]->Uninit();
	m_scene[2]->Uninit();
	m_scene[1]->Uninit();
	m_scene[0]->Uninit();

	//	各シーンのメモリの解放
	delete m_scene[3];
	delete m_scene[2];
	delete m_scene[1];
	delete m_scene[0];
}

//	更新処理
void SceneManager::Update()
{
	m_scene[m_sceneState]->Update();	//	各シーンのUpdate関数の呼び出し
	Fade::Update();
}

//	描画処理
void SceneManager::Draw()
{
	m_scene[m_sceneState]->Draw();		//	各シーンのDraw関数の呼び出し
	Fade::Draw();
}

//	シーン遷移処理
void SceneManager::ChangeSceneState()
{	
	bool flg = GetFlag();
	switch (m_sceneState)
	{
	case SCENE_TITLE:
		m_scene[m_sceneState]->Uninit();
		if (flg == true)
		{
			m_sceneState = SCENE_TUTORIAL;	//	チュートリアルへ遷移
			m_scene[m_sceneState]->Init();
		}
		else if (flg == false)
		{
			m_sceneState = SCENE_GAME;		//	ゲームへ遷移
			m_scene[m_sceneState]->Init();
		}
		break;
	case SCENE_TUTORIAL:
		m_scene[m_sceneState]->Uninit();
		m_sceneState = SCENE_GAME;			//	ゲームへ遷移
		m_scene[m_sceneState]->Init();
		break;
	case SCENE_GAME:
		m_scene[m_sceneState]->Uninit();
		m_sceneState = SCENE_RESULT;		//	リザルトへ遷移
		m_scene[m_sceneState]->Init();
		break;
	case SCENE_RESULT:
		m_scene[m_sceneState]->Uninit();
		m_sceneState = SCENE_TITLE;			//	タイトルへ遷移
		m_scene[m_sceneState]->Init();
		break;
	}
}

SceneBase * SceneManager::SetSceneGame()
{
	return m_scene[3];
}
 