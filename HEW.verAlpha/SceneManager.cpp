/*==============================================

	[SceneManager.cpp]
	Author : 出合翔太

===============================================*/
#include "main.h"
#include "input.h"
#include "SceneGame.h"
#include "SceneManager.h"

//	グローバル変数
SceneBase			*SceneManager::scene[SCENE_NUMBER];
SCENE_STATE			SceneManager::scenestate;
LPDIRECT3DDEVICE9	SceneManager::p3DDevice;

//	初期化処理
void SceneManager::Init()
{
	p3DDevice = GetD3DDevice();	//	デバイスの取得
	scene[0] = new SceneGame;	//	シーンのインスタンス生成
	scenestate = SCENE_GAME;	//	初期シーンの設定
	scene[scenestate]->Init();	//	初期シーンの初期化
}

//	終了処理
void SceneManager::Uninit()
{
	scene[0]->Uninit();
	delete scene[0];
}

//	更新処理
void SceneManager::Update()
{
	if (Input::GP_IsTrigger(0,BUTTON_2)) 
	{
		SceneManager::ChangeSceneState();
	}
	scene[scenestate]->Update();
}

//	描画処理
void SceneManager::Draw()
{
	scene[scenestate]->Draw();
}

//	シーン遷移処理
void SceneManager::ChangeSceneState()
{
	switch (scenestate)
	{
	case SCENE_GAME:
		scene[scenestate]->Uninit();
	}
}
