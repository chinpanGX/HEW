/*===================================================

	[SceneTitle.cpp]
	概要 ：タイトルシーンの管理をする
	Author : 出合翔太

====================================================*/

#include "SceneTitle.h"
#include "SceneManager.h"
#include "Controller.h"

static bool SelectFlag;

void SceneTitle::Init()
{
	m_Color = D3DCOLOR_RGBA(255, 255, 255, 100);
	SelectFlag = false;
	m_bEnd = false;
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void SceneTitle::Uninit()
{

}

void SceneTitle::Update()
{
	//	チュートリアル選択
	if (KeyBoard::IsTrigger(DIK_S) || GamePad::IsTrigger(0,BUTTON_DOWN))
	{
		SelectFlag = true;
	}
	//	ゲーム選択
	if (KeyBoard::IsTrigger(DIK_W) || GamePad::IsTrigger(0,BUTTON_UP))
	{
		SelectFlag = false;
	}
	if (!m_bEnd)
	{
		//	画面遷移
		if (KeyBoard::IsTrigger(DIK_T) || GamePad::IsTrigger(0,BUTTON_2))
		{
			m_bEnd = true;
			Fade::Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		}
	}
	else 
	{
		if (!Fade::IsFade())
		{
			SceneManager::ChangeSceneState();
		}
  }
}

void SceneTitle::Draw()
{
	D3DCOLOR gamecolor = D3DCOLOR_RGBA(255, 255, 255, 255);
	D3DCOLOR tutorialcolor = D3DCOLOR_RGBA(255, 255, 255, 255);
	if (SelectFlag == false)
	{
		tutorialcolor = m_Color;
	}
	else if (SelectFlag == true)
	{
		gamecolor = m_Color;
	}
	m_Sprite.Draw(TEXTURE_TITLE,0.0f,0.0f);
	m_Sprite.Draw(TEXTURE_UI, 640.0f, 540.0f, 30.0f, 360.0f, 1008.0f, 300.0f, 30.0f, 50.0f, 0.75f, 0.75f, 0.0f,gamecolor);//ゲームスタートの描画	
	m_Sprite.Draw(TEXTURE_UI, 640.0f, 740.0f, 30.0f, 660.0f, 1008.0f, 250.0f, 30.0f, 50.0f, 0.75f, 0.75f, 0.0f,tutorialcolor);//チュートリアルの描画
}

bool GetFlag()
{
	return SelectFlag;
}
