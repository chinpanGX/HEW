/*===================================================

	[SceneResult.cpp]
	概要 : リザルトシーンを管理する
	Author : 出合翔太

====================================================*/

#include "SceneResult.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Fade.h"
#include "Score.h"
#include "mondai.h"
#include "Sound.h"

void SceneResult::Init()
{
	m_bEnd = false;
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
	Sound::Play(S_BGM_TITLE);
}

void SceneResult::Uninit()
{
	
}

void SceneResult::Update()
{
	if (!m_bEnd)
	{
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

void SceneResult::Draw()
{
	m_Sprite.Draw(TEXTURE_INDEX_RESULT,0.0f,0.0f);
	Score_Draw(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT *0.5f, GetScore(), 1);
}
