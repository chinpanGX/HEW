/*===================================================

	[SceneTitle.cpp]
	Author : èoçá„ƒëæ

====================================================*/

#include "SceneTitle.h"

void SceneTitle::Init()
{
	m_Camera.Init();
	m_Map.Init();
}

void SceneTitle::Uninit()
{
	m_Camera.Uninit();
	m_Map.Uninit();
}

void SceneTitle::Update()
{
	m_Camera.Update();
}

void SceneTitle::Draw()
{
	m_Camera.Set();
	m_Map.Draw();
}
