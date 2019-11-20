/*===================================================

	[SceneTitle.cpp]
	Author : o‡ãÄ‘¾

====================================================*/

#include "SceneTitle.h"
#include <map>
#include "main.h"
#include "Map.h"

SceneTitle::SceneTitle()
{
	m_pTitleCamera = new TitleCamera;
}

SceneTitle::~SceneTitle()
{
	delete m_pTitleCamera;
}

void SceneTitle::Init()
{
	m_pTitleCamera->Init();
	Map::Init();
}

void SceneTitle::Uninit()
{
	m_pTitleCamera->Uninit();
	Map::Uninit();
}

void SceneTitle::Update()
{
	m_pTitleCamera->Update();
}

void SceneTitle::Draw()
{
	m_pTitleCamera->Set();
	Map::Draw();
}
