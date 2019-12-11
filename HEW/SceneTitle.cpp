/*===================================================

	[SceneTitle.cpp]
	Author : èoçá„ƒëæ

====================================================*/

#include "SceneTitle.h"
#include "SceneManager.h"
#include "Controller.h"

void SceneTitle::Init()
{
	//m_Camera.Init();
	//m_Map.Init();
	m_count.Init();
}

void SceneTitle::Uninit()
{
	//m_Camera.Uninit();
	//m_Map.Uninit();
}

void SceneTitle::Update()
{
	/*m_Camera.Update();*/
	m_count.Update();

	if (KeyBoard::IsTrigger(DIK_W))
	{
		SceneManager::ChangeSceneState();
	}
}

void SceneTitle::Draw()
{
	/*m_Camera.Set();
	m_Map.Draw();*/
	m_count.Draw();
}
