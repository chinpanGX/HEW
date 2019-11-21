/*===================================================

	[SceneTitle.cpp]
	Author : èoçá„ƒëæ

====================================================*/

#include "SceneTitle.h"
#include <map>
#include "main.h"
#include "Map.h"

SceneTitle::SceneTitle()
{

}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Init()
{
	m_TitleCamera.Init();
	Map::Init();
}

void SceneTitle::Uninit()
{
	m_TitleCamera.Uninit();
	Map::Uninit();
}

void SceneTitle::Update()
{
	m_TitleCamera.Update();
}

void SceneTitle::Draw()
{
	m_TitleCamera.Set();
	Map::Draw();
}
