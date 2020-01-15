/*===================================================

	[SceneTitle.cpp]
	Author : 出合翔太

====================================================*/

#include "SceneTitle.h"
#include "SceneManager.h"
#include "Controller.h"

void SceneTitle::Init()
{
	m_bEnd = false;
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
	//m_Camera.Init();
	//m_Map.Init();
	//m_count.Init();
}

void SceneTitle::Uninit()
{
	//m_Camera.Uninit();
	//m_Map.Uninit();
}

void SceneTitle::Update()
{
	/*m_Camera.Update();*/
	//m_count.Update();
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

void SceneTitle::Draw()
{
	/*m_Camera.Set();
	m_Map.Draw();*/
//	m_count.Draw();
}
