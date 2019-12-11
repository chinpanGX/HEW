/*=======================================================

	[SecneModeSelect.cpp]
	Author :霞和希 

=======================================================*/

#include "SceneModeSelect.h"
#include "SceneManager.h"
#include "Controller.h"
#include "main.h"

static bool flg=true;
//	初期化
void SceneModeSelect::Init()
{

}

//	終了処理
void SceneModeSelect::Uninit()
{

	//flg = Getflg();

		if (flg == true)
		{
			//チュートリアル
			m_Sprite.Draw(TEXTURE_INDEX_SCENE_TUTORIAL, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 20.0f, 2.0f, 0.0f, 5.0f, 0.0f);
		}
		else if (flg == false)
		{
			//ゲーム
			m_Sprite.Draw(TEXTURE_INDEX_SCENE_GAME, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f);
		}

}

//	更新処理
void SceneModeSelect::Update()
{

	if (KeyBoard::IsTrigger(DIK_Q))
	{
		flg = true;
	}
	if (KeyBoard::IsTrigger(DIK_E))
	{
		flg = false;
	}
	if (KeyBoard::IsTrigger(DIK_W))
	{
		SceneManager::ChangeSceneState();
	}
}

//	描画処理
void SceneModeSelect::Draw()
{
	//m_Sprite.Draw(TEXTURE_INDEX_MODESELECT, 0.0f, 0.0f);
	
	//m_Sprite.Draw; //(通常のやつ)
	//m_Sprite.Draw; //(通常のやつ)

		if (flg == true)
		{
			m_Sprite.Draw(TEXTURE_INDEX_SCENE_TUTORIAL,0.0f,0.0f,0.0f,0.0f,500.0f,500.0f,255.0f,255.0f,255.0f,255.0f);// (色変更)
		}
		else if (flg == false)
		{
			m_Sprite.Draw(TEXTURE_INDEX_SCENE_GAME, 0.0f, 0.0f, 0.0f, 0.0f, 500.0f, 500.0f, 20.0f,200.0f, 0.0f, 0.0f);// (色変更)
		}
	
}


bool Getflg()
{
	return flg;
}
