/*======================================================

	[SceneTutorial.cpp]
	概要 : チュートリアルシーンを管理する
	Author : 出合翔太

======================================================*/

#include "SceneTutorial.h"
#include "SceneManager.h"
#include "Controller.h"

void SceneTutorial::Init()
{
	m_bEnd = false;
	Fade::Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void SceneTutorial::Uninit()
{

}

void SceneTutorial::Update()
{
	if (!m_bEnd)
	{
		if (KeyBoard::IsTrigger(DIK_T) || GamePad::IsTrigger(0, BUTTON_2))
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

void SceneTutorial::Draw()
{
	m_Sprite.Draw(TEXTURE_INDEX_SAMPLE,0.0f,0.0f);
}
