/*==============================================

	[SceneManager.cpp]
	Author : 出合翔太

===============================================*/
#include "main.h"
#include "input.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneModeSelect.h"
#include "SceneTutorial.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneDebug.h"


//	グローバル変数
SceneBase			*SceneManager::scene[SCENE_NUMBER];
SCENE_STATE			SceneManager::scenestate;
LPDIRECT3DDEVICE9	SceneManager::p3DDevice;

//	初期化処理
void SceneManager::Init()
{
	p3DDevice = GetD3DDevice();		//	デバイスの取得

	//	各シーンのメモリの確保
	scene[0] = new SceneTitle;			
	scene[1] = new SceneModeSelect;		
	scene[2] = new SceneTutorial;		
	scene[3] = new SceneGame;			
	scene[4] = new SceneResult;
	scene[5] = new SceneDebug;

	scenestate = SCENE_TITLE;			//	初期シーンの設定	main.hのenumで宣言しているオブジェクト名を設定
	scene[scenestate]->Init();			//	初期シーンの初期化	設定したオブジェクト名のInit関数を呼び出す。
}

//	終了処理
void SceneManager::Uninit()
{
	//	各シーンのUninit関数を呼び出す
	scene[5]->Uninit();
	scene[4]->Uninit();
	scene[3]->Uninit();
	scene[2]->Uninit();
	scene[1]->Uninit();
	scene[0]->Uninit();

	//	各シーンのメモリの解放
	delete scene[5];
	delete scene[4];
	delete scene[3];
	delete scene[2];
	delete scene[1];
	delete scene[0];
}

//	更新処理
void SceneManager::Update()
{
	//	Input関数を呼び出す
	if (Input::GP_IsTrigger(0,BUTTON_2)) 
	{
		SceneManager::ChangeSceneState();	//	シーン遷移処理 -> 画面の切り替え
	}
	scene[scenestate]->Update();	//	切り替えたシーンのUpdate関数を呼び出す
}

//	描画処理
void SceneManager::Draw()
{
	scene[scenestate]->Draw();	//	各シーンのDraw関数を呼び出す。
}

//	シーン遷移処理
void SceneManager::ChangeSceneState()
{
	switch (scenestate)
	{
	case SCENE_TITLE:
		scene[scenestate]->Uninit();
		scenestate = SCENE_MODESELECT;
		scene[scenestate]->Init();
	case SCENE_MODESELECT:
		scene[scenestate]->Uninit();
		scene[scenestate]->Init();
	case SCENE_TUTORIAL:
		scene[scenestate]->Uninit();
	case SCENE_GAME:
		scene[scenestate]->Uninit();
	case SCENE_RESULT:
		scene[scenestate]->Uninit();
	case SCENE_DEBUG:
		scene[scenestate]->Uninit();
	}
}
 