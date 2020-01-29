/*==================================

	[SceneGame.cpp]
	概要 : ゲームシーンを管理する
	Author : 出合翔太

===================================*/

#include "SceneGame.h"
#include "SceneManager.h"
#include "Controller.h"

//	ゲームの初期化処理
void SceneGame::Init()
{
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

//	ゲームの終了処理
void SceneGame::Uninit()
{
	
}

//	ゲームの更新処理
void SceneGame::Update()
{
	
}

//	ゲームの描画処理
void SceneGame::Draw()
{
	
}

bool SceneGame::EndCheck()
{
	return false;
}

