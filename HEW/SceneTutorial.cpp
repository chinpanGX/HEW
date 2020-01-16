/*======================================================

	[SceneTutorial.cpp]
	Author : èoçá„ƒëæ

======================================================*/

#include "SceneTutorial.h"
#include "SceneManager.h"
#include "Controller.h"

void SceneTutorial::Init()
{
	m_bEnd = false;
}

void SceneTutorial::Uninit()
{

}

void SceneTutorial::Update()
{
	if (!m_bEnd)
	{
		if (KeyBoard::IsTrigger(DIK_T))
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
