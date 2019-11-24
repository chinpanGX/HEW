/*===================================================

	[SceneResult.cpp]
	Author : èoçá„ƒëæ

====================================================*/

#include "SceneResult.h"
#include "SceneManager.h"
#include "Controller.h"

void SceneResult::Init()
{

}

void SceneResult::Uninit()
{

}

void SceneResult::Update()
{

	if (KeyBoard::IsTrigger(DIK_W))
	{
		SceneManager::ChangeSceneState();
	}
}

void SceneResult::Draw()
{
	m_Sprite.Draw(TEXTURE_INDEX_RESULT,0.0f,0.0f);
}
