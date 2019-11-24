/*=======================================================

	[SecneModeSelect.cpp]
	Author : 出合翔太

=======================================================*/

#include "SceneModeSelect.h"
#include "SceneManager.h"
#include "Controller.h"

//	初期化
void SceneModeSelect::Init()
{

}

//	終了処理
void SceneModeSelect::Uninit()
{
	
}

//	更新処理
void SceneModeSelect::Update()
{
	if (KeyBoard::IsTrigger(DIK_W))
	{
		SceneManager::ChangeSceneState();
	}
}

//	描画処理
void SceneModeSelect::Draw()
{
	m_Sprite.Draw(TEXTURE_INDEX_MODESELECT, 0.0f, 0.0f);
}
